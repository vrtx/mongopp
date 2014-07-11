# Set up the source files for each module
set(BSON_SRCS
              array.cpp
              bcontainer.cpp
              document.cpp
              element.cpp)

set(BSON_HDRS
              array.hpp
              bcontainer.hpp
              document.hpp
              element.hpp)

add_library(bson STATIC ${BSON_HDRS} ${BSON_SRCS})

target_link_libraries(bson
                           pthread
                           tcmalloc
                           ${LIBMONGOC_LIBRARIES}
                           ${LIBBSON_LIBRARIES})

# Tests
add_executable(array_test array_test.cpp)
add_executable(document_test document_test.cpp)

target_link_libraries(array_test bson unittest)
target_link_libraries(document_test bson unittest)

add_test(array_test array_test)
add_test(document_test document_test)
