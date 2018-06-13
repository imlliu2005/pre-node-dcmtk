#include <nan.h>
#include "parsedicom.cc"

void Init(v8::Local<v8::Object> exports) {
  parsedicom_init(exports);
}

NODE_MODULE(dcmtk, Init)
