include(FindPkgConfig QUIET)
pkg_check_modules(PC_UUID QUIET "uuid")

find_path(
    UUID_INCLUDE_DIRS
    NAMES "uuid/uuid.h"
    HINTS ${PC_UUID_INCLUDE_DIRS}
)

find_library(
    UUID_LIBRARIES
    NAMES uuid
    HINTS ${PC_UUID_LIBRARIES}
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(UUID REQUIRED_VARS UUID_LIBRARIES UUID_INCLUDE_DIRS)
mark_as_advanced(UUID_LIBRARIES UUID_INCLUDE_DIRS)
