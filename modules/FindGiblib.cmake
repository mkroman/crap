find_path(GIBLIB_INCLUDE_DIR giblib.h PATH_SUFFIXES giblib)
find_library(GIBLIB_LIBRARY NAMES giblib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Giblib  DEFAULT_MSG
                                  GIBLIB_LIBRARY GIBLIB_INCLUDE_DIR)
