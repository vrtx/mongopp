# Set up the source files for each module
set(TEST_SRCS unittest.cpp)

set(TEST_HDRS unittest.hpp)

add_library(unittest ${TEST_HDRS} ${TEST_SRCS})

target_link_libraries(unittest
                                pthread
                                tcmalloc)
