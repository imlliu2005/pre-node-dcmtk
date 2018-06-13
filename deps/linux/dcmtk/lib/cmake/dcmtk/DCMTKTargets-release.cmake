#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ofstd" for configuration "Release"
set_property(TARGET ofstd APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ofstd PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "nsl;pthread"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libofstd.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS ofstd )
list(APPEND _IMPORT_CHECK_FILES_FOR_ofstd "${_IMPORT_PREFIX}/lib/libofstd.a" )

# Import target "oflog" for configuration "Release"
set_property(TARGET oflog APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(oflog PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "ofstd"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/liboflog.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS oflog )
list(APPEND _IMPORT_CHECK_FILES_FOR_oflog "${_IMPORT_PREFIX}/lib/liboflog.a" )

# Import target "dcmdata" for configuration "Release"
set_property(TARGET dcmdata APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(dcmdata PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "ofstd;oflog;/usr/lib/x86_64-linux-gnu/libz.so"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libdcmdata.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS dcmdata )
list(APPEND _IMPORT_CHECK_FILES_FOR_dcmdata "${_IMPORT_PREFIX}/lib/libdcmdata.a" )

# Import target "i2d" for configuration "Release"
set_property(TARGET i2d APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(i2d PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "dcmdata"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libi2d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS i2d )
list(APPEND _IMPORT_CHECK_FILES_FOR_i2d "${_IMPORT_PREFIX}/lib/libi2d.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
