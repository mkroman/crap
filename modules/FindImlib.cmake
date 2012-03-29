find_path(IMLIB_INCLUDE_DIR Imlib2.h)
find_library(IMLIB_LIBRARY NAMES Imlib2)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Imlib DEFAULT_MSG
                                  IMLIB_LIBRARY IMLIB_INCLUDE_DIR)
