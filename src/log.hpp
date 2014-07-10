#pragma once

// display debug log message in the format:
// [mongo-sim]: [file.c:line]: message
#define DEBUG(MSG, ...) do {                   \
    fprintf(stderr,                            \
            "[mongo-sim] [%s:%d]: " MSG "\n",  \
            __FILE__,                          \
            __LINE__,                          \
            ##__VA_ARGS__);                    \
} while(0)

// display log message in the format:
// [mongo-sim]: message
#define LOG(MSG, ...) do {                     \
    fprintf(stderr,                            \
            "[mongo-sim] " MSG "\n",           \
            ##__VA_ARGS__);                    \
} while(0)
