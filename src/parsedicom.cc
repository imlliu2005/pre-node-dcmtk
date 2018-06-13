#include <nan.h>

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/ofstd/ofstream.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/cmdlnarg.h"
#include "dcmtk/ofstd/ofconapp.h"
#include "dcmtk/ofstd/ofstd.h"
#include "dcmtk/dcmdata/dcuid.h"      /* for dcmtk version name */
#include "dcmtk/dcmdata/dcistrmz.h"   /* for dcmZlibExpectRFC1950Encoding */
#include "dcmtk/dcmdata/dcjson.h"

#define INCLUDE_CSTDLIB
#define INCLUDE_CSTRING
#include "dcmtk/ofstd/ofstdinc.h"

#ifdef WITH_ZLIB
#include <zlib.h>                     /* for zlibVersion() */
#endif
#ifdef DCMTK_ENABLE_CHARSET_CONVERSION
#include "dcmtk/ofstd/ofchrenc.h"     /* for OFCharacterEncoding */
#endif
#define OFFIS_CONSOLE_APPLICATION "dcmdump"
static OFLogger dcmdumpLogger = OFLog::getLogger("dcmtk.apps.");
static OFCmdUnsignedInt maxReadLength = 4096; // default is 4 KB

#include "iconv.h"
#include <stdlib.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <string.h>  
#include <sys/stat.h>

struct iequal
{
    bool operator()(int c1, int c2) const
    {
        return std::toupper(c1) == std::toupper(c2);
    }
};

bool iequals(const std::string&, const std::string&);
bool iequals(const std::string& str1, const std::string& str2)
{
  return str1.size() == str2.size() && std::equal(str1.begin(), str1.end(), str2.begin(), iequal());
}

void collectElement(std::vector<DcmObject*>& l, DcmObject* container, OFString& encode) {
  DcmObject* obj = NULL;
  while(obj = container->nextInContainer(obj)) {
    if (obj->isLeaf() && obj->getLength() < 256) {
      DcmTag tag(obj->getTag());
      OFString tagName = tag.getTagName();
      if (obj->getTag().getXTag().toString() == "(0008,0005)") {
        DcmElement* e = (DcmElement*)obj;
        e->getOFStringArray(encode);
      }
      if (tagName != "Unknown Tag & Data") {
        OFString s;
        DcmElement* e = (DcmElement*)obj;
        e->getOFStringArray(s);
        l.push_back(obj);
      }
    } else {
//      collectElement(l, obj, encode);
    }
  }
}

static const int BUFFER_LENGTH = 1024;
static const int OUT_BUFFER_LENGTH = 2 * 1024;
static char* instrtmp = new char[BUFFER_LENGTH];
static char* outstrtmp = new char[OUT_BUFFER_LENGTH];
static iconv_t sharedIconv = 0;


// hack here. we only use one encoding for now. should make a encoding map to select one from it.
int code_convert(char *from_charset, char *to_charset, char *inbuf, unsigned long inlen,  
  char *outbuf, unsigned long outlen) {  

  char **pin = &inbuf;  
  char **pout = &outbuf;  

  if (sharedIconv == 0) {
    sharedIconv = iconv_open(to_charset, from_charset);
  }

  if (sharedIconv == 0)  
    return -1;  
  memset(outbuf, 0, inlen * 2 + 1);  
  if (iconv(sharedIconv, pin, &inlen, pout, &outlen) == -1)  
      return -1;
  *pout = "\0";

  return 0;  
}

int g2u(char *inbuf, unsigned long inlen, char *outbuf, unsigned long outlen) {  
  return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}

const char* encodingConvert(const char* input) {
  int length = strlen(input);
  if (length > BUFFER_LENGTH) {
    return input;
  }
  strncpy(instrtmp, input, length);
  int ret = g2u(instrtmp, length, outstrtmp, OUT_BUFFER_LENGTH);
  if (ret != 0) {
    return input;
  }
  return outstrtmp;
}

void dumpIntoObject(v8::Local<v8::Object> &out, std::vector<DcmObject*>& l, const OFString& encode) {
  for (auto iter = l.begin(); iter != l.end(); iter++) {
    DcmObject* obj = *iter;
    DcmTag tag(obj->getTag());
    OFString s;
    DcmElement* e = (DcmElement*)obj;
    e->getOFStringArray(s);
    const char* outStr = s.c_str();
    if (obj->isAffectedBySpecificCharacterSet() || 
      obj->getTag().getXTag().toString() == "(0010,0040)" // PatientSex
    ) {
      if (iequals(encode.c_str(), "gb18030") 
        || iequals(encode.c_str(), "gb2312")
        || iequals(encode.c_str(), "gbk"))
        {
          outStr = encodingConvert(outStr);
        }
        
    }
    
    out->Set(Nan::New(tag.getTagName()).ToLocalChecked(), 
      Nan::New(outStr).ToLocalChecked());
  }
}

static int dumpFile(//STD_NAMESPACE ostream &out,
                    v8::Local<v8::Object>& out,
                    const OFFilename &ifname,
                    const E_FileReadMode readMode,
                    const E_TransferSyntax xfer,
                    const OFBool loadIntoMemory,
                    const OFBool stopOnErrors,
                    const OFBool convertToUTF8,
                    const DcmTagKey &stopParsingAtElement)
{
    int result = 0;
    if (ifname.isEmpty())
    {
        OFLOG_ERROR(dcmdumpLogger, OFFIS_CONSOLE_APPLICATION << ": invalid filename: <empty string>");
        return 1;
    }

    DcmFileFormat dfile;
    DcmObject *dset = &dfile;
    if (readMode == ERM_dataset) dset = dfile.getDataset();
    OFCondition cond;

    if (stopParsingAtElement == DCM_UndefinedTagKey)
    {
        cond = dfile.loadFile(ifname, xfer, EGL_noChange, OFstatic_cast(Uint32, maxReadLength), readMode);
    }
    else
    {
        // instead of using loadFile(), we call loadFileUntilTag().
        cond = dfile.loadFileUntilTag(ifname, xfer, EGL_noChange, OFstatic_cast(Uint32, maxReadLength), readMode, stopParsingAtElement);
    }
    if (cond.bad())
    {
        OFLOG_ERROR(dcmdumpLogger, OFFIS_CONSOLE_APPLICATION << ": " << cond.text()
            << ": reading file: "<< ifname);
        result = 1;
        if (stopOnErrors) return result;
    }

    if (loadIntoMemory) dfile.loadAllDataIntoMemory();

#ifdef DCMTK_ENABLE_CHARSET_CONVERSION
    if (convertToUTF8)
    {
        OFLOG_INFO(dcmdumpLogger, "converting all element values that are affected by Specific Character Set (0008,0005) to UTF-8");
        cond = dfile.convertToUTF8();
        if (cond.bad())
        {
            OFLOG_FATAL(dcmdumpLogger, cond.text() << ": converting file to UTF-8: " << ifname);
            result = 1;
            if (stopOnErrors) return result;
        }
    }
#else
    // avoid compiler warning on unused variable
    (void)convertToUTF8;
#endif
    DcmObject* obj = NULL;
    std::vector<DcmObject*> l;
    OFString encode;
    while(obj = dfile.nextInContainer(obj)) {
      // handle the obj
      if (obj->isLeaf()) {
      } else {
        collectElement(l, obj, encode);
      }
    }
    dumpIntoObject(out, l, encode);
    return result;
}

static bool logConfigured = false;

void parseDicom(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (!logConfigured) {
    logConfigured = true;
    OFLog::configure(OFLogger::LogLevel::ERROR_LOG_LEVEL);
  }
  const char* path = *Nan::Utf8String(info[0]->ToString());
  OFFilename fileName(path);
  E_FileReadMode readMode = ERM_autoDetect;
  E_TransferSyntax xfer = EXS_Unknown;
  OFBool loadIntoMemory = OFTrue;
  OFBool stopOnErrors = OFTrue;
  OFBool convertToUTF8 = OFFalse;
  DcmTagKey stopParsingBeforeElement = DCM_UndefinedTagKey;
  // std::ostringstream stream;
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  int result = dumpFile(obj, fileName, readMode, xfer,
    loadIntoMemory, stopOnErrors, 
    convertToUTF8, stopParsingBeforeElement);
  if (result == 1) {
    info.GetReturnValue().Set(Nan::Null());
  } else {
    info.GetReturnValue().Set(obj);
  }  
}

void parsedicom_init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("parseDicom").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(parseDicom)->GetFunction());
}
