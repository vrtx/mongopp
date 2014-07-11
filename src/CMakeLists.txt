add_subdirectory(bson)

# Set the sources and headers to build from
set(SRCS client.cpp
         collection.cpp
         cursor.cpp
         database.cpp)

set(HDRS   client.hpp
           collection.hpp
           cursor.hpp
           database.hpp
           log.hpp
           mongo_exception.hpp)

# Build the target library
add_library(mongopp SHARED ${SRCS} ${HDRS})
target_link_libraries(mongopp pthread
                              bson
                              ${LIBMONGOC_LIBRARIES}
                              ${LIBBSON_LIBRARIES})

# Build the tests
# add_executable(statistics_test statistics_test.cpp)
# target_link_libraries(statistics_test unittest statistics)
# add_test(statistics_test statistics_test)

install(TARGETS mongopp DESTINATION lib)
