#pragma once

// display debug log message in the format:
// [mongo-cpp]: [file.c:line]: message
#define DEBUG(MSG, ...) do {                   \
    fprintf(stderr,                            \
            "[mongo-cpp] [%s:%d]: " MSG "\n",  \
            __FILE__,                          \
            __LINE__,                          \
            ##__VA_ARGS__);                    \
} while(0)

// display log message in the format:
// [mongo-cpp]: message
#define LOG(MSG, ...) do {                     \
    fprintf(stderr,                            \
            "[mongo-cpp] " MSG "\n",           \
            ##__VA_ARGS__);                    \
} while(0)
