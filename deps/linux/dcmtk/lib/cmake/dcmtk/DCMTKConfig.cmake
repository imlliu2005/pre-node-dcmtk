#
# DCMTKConfig.cmake - DCMTK CMake configuration file for external projects
#


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was DCMTKConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

####################################################################################

# Basic version information
SET(DCMTK_MAJOR_VERSION 3)
SET(DCMTK_MINOR_VERSION 6)
SET(DCMTK_BUILD_VERSION 3)

# DCMTK libraries and modules
SET(DCMTK_MODULES "ofstd;oflog;dcmdata")
SET(DCMTK_LIBRARIES "ofstd;oflog;dcmdata;i2d")

# Optional DCMTK 3rd party libraries
SET(DCMTK_WITH_TIFF OFF)
SET(DCMTK_WITH_PNG OFF)
SET(DCMTK_WITH_XML OFF)
SET(DCMTK_WITH_ZLIB ON)
SET(DCMTK_WITH_OPENSSL ON)
SET(DCMTK_WITH_SNDFILE OFF)
SET(DCMTK_WITH_ICONV OFF)
SET(DCMTK_WITH_STDLIBC_ICONV ON)
SET(DCMTK_WITH_ICU OFF)
SET(DCMTK_WITH_WRAP OFF)
SET(DCMTK_WITH_DOXYGEN OFF)

# Dictionary-related
SET(DCMTK_ENABLE_BUILTIN_DICTIONARY ON)
SET(DCMTK_ENABLE_EXTERNAL_DICTIONARY ON)
SET(DCMTK_ENABLE_PRIVATE_TAGS OFF)

# Compiler / standard library features
SET(DCMTK_ENABLE_CXX11 OFF)
SET(DCMTK_CXX11_FLAGS -std=c++11)
SET(DCMTK_ENABLE_STL OFF)

# DCMTK shared libraries
SET(DCMTK_SHARED_LIBRARIES OFF)
SET(DCMTK_SINGLE_SHARED_LIBRARY OFF)

# DCMTK additional options
SET(DCMTK_WITH_THREADS ON)
SET(DCMTK_OVERWRITE_WIN32_COMPILER_FLAGS OFF)
SET(DCMTK_WIDE_CHAR_FILE_IO_FUNCTIONS OFF)
SET(DCMTK_WIDE_CHAR_MAIN_FUNCTION OFF)
SET(DCMTK_ENABLE_LFS lfs64)

SET_AND_CHECK(DCMTK_TARGETS "${PACKAGE_PREFIX_DIR}/lib/cmake/dcmtk/DCMTKTargets.cmake")

####### Expanded from @DCMTK_CONFIG_CODE@ #######
list(APPEND DCMTK_INCLUDE_DIRS "${PACKAGE_PREFIX_DIR}/include")
##################################################

# Compatibility: This variable is deprecated
SET(DCMTK_INCLUDE_DIR ${DCMTK_INCLUDE_DIRS})

IF(NOT DCMTK_TARGETS_IMPORTED)
  SET(DCMTK_TARGETS_IMPORTED 1)
  INCLUDE(${DCMTK_TARGETS})
ENDIF(NOT DCMTK_TARGETS_IMPORTED)
