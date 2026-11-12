
set(DEP_CMAKE_OPTS "-DCMAKE_POSITION_INDEPENDENT_CODE=ON")

# GCC 15 defaults to -std=gnu23 (C23), where 'bool' is a keyword. Older bundled
# C libraries still do `typedef _Bool bool;` (e.g. Blosc 1.17), which is a hard
# error under C23. Pin the C standard to C17 for all dependency C code.
list(APPEND DEP_CMAKE_OPTS "-DCMAKE_C_FLAGS:STRING=-std=gnu17")

include("deps-unix-common.cmake")

# Some Linuxes may have very old libpng, so it's best to bundle it instead of relying on the system version.
# find_package(PNG QUIET)
# if (NOT PNG_FOUND)
#     message(WARNING "No PNG dev package found in system, building static library. You should install the system package.")
# endif ()