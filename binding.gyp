{
  "targets": [
    {
      "target_name": "dcmtk",
      "sources": [ "src/dcmtk.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          },
          'include_dirs': [
            'deps/darwin/dcmtk/include',
            'deps/darwin/libiconv/include'
          ],
          'libraries': [
            '../deps/darwin/dcmtk/lib/libofstd.a',
            '../deps/darwin/dcmtk/lib/libdcmdata.a',
            '../deps/darwin/dcmtk/lib/liboflog.a',
            '../deps/darwin/libiconv/lib/libcharset.a',
            '../deps/darwin/libiconv/lib/libiconv.a',
            # '../deps/darwin/lib/libdcmjpeg.a',
            # '../deps/darwin/lib/libdcmpmap.a',
            # '../deps/darwin/lib/libdcmrt.a',
            # '../deps/darwin/lib/libdcmtls.a',
            # '../deps/darwin/lib/libi2d.a',
            # '../deps/darwin/lib/libijg8.a',
            # '../deps/darwin/lib/libcharls.a',
            # '../deps/darwin/lib/libdcmdsig.a',
            # '../deps/darwin/lib/libdcmimgle.a',
            # '../deps/darwin/lib/libdcmjpls.a',
            # '../deps/darwin/lib/libdcmpstat.a',
            # '../deps/darwin/lib/libdcmseg.a',
            # '../deps/darwin/lib/libdcmtract.a',
            # '../deps/darwin/lib/libijg12.a',
            # '../deps/darwin/lib/libcmr.a',
            # '../deps/darwin/lib/libdcmfg.a',
            # '../deps/darwin/lib/libdcmiod.a',
            # '../deps/darwin/lib/libdcmnet.a',
            # '../deps/darwin/lib/libdcmqrdb.a',
            # '../deps/darwin/lib/libdcmsr.a',
            # '../deps/darwin/lib/libdcmwlm.a',
            # '../deps/darwin/lib/libijg16.a'
            #'../deps/darwin/lib/libdcmtk.13.dylib',
            # "-Wl,-rpath,./deps/darwin/lib"
          ],
        }],
        ['OS=="linux"', {
          'include_dirs': [
            'deps/linux/dcmtk/include',
          ],
          'libraries': [
            # '../deps/linux/dcmtk/lib/libofstd.a',
            # '../deps/linux/dcmtk/lib/libdcmdata.a',
            # '../deps/linux/dcmtk/lib/liboflog.a',
            '../deps/linux/libiconv/lib/libcharset.a',
            '../deps/linux/libiconv/lib/libiconv.a',
            # '../deps/linux/dcmtk/lib/libdcmjpeg.a',
            # '../deps/linux/dcmtk/lib/libdcmpmap.a',
            # '../deps/linux/dcmtk/lib/libdcmrt.a',
            # '../deps/linux/dcmtk/lib/libdcmtls.a',
            # '../deps/linux/dcmtk/lib/libi2d.a',
            # '../deps/linux/dcmtk/lib/libijg8.a',
            # '../deps/linux/dcmtk/lib/libcharls.a',
            # '../deps/linux/dcmtk/lib/libdcmdsig.a',
            # '../deps/linux/dcmtk/lib/libdcmimgle.a',
            # '../deps/linux/dcmtk/lib/libdcmjpls.a',
            # '../deps/linux/dcmtk/lib/libdcmpstat.a',
            # '../deps/linux/dcmtk/lib/libdcmseg.a',
            # '../deps/linux/dcmtk/lib/libdcmtract.a',
            # '../deps/linux/dcmtk/lib/libijg12.a',
            # '../deps/linux/dcmtk/lib/libcmr.a',
            # '../deps/linux/dcmtk/lib/libdcmfg.a',
            # '../deps/linux/dcmtk/lib/libdcmiod.a',
            # '../deps/linux/dcmtk/lib/libdcmnet.a',
            # '../deps/linux/dcmtk/lib/libdcmqrdb.a',
            # '../deps/linux/dcmtk/lib/libdcmsr.a',
            # '../deps/linux/dcmtk/lib/libdcmwlm.a',
            # '../deps/linux/dcmtk/lib/libijg16.a'
          ],
          'ldflags': [ "-Wl,--whole-archive", '../deps/linux/dcmtk/lib/libofstd.a',
            '../deps/linux/dcmtk/lib/libdcmdata.a',
            '../deps/linux/dcmtk/lib/liboflog.a', 
            "-Wl,--no-whole-archive" ]
        }]
      ]
    }
  ]
}
