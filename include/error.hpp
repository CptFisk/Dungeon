#pragma once
#include <assert.h>

// Custom assert macro with a message
#define ASSERT_WITH_MESSAGE(condition, message)                                                                                       \
    do {                                                                                                                              \
        if (!(condition)) {                                                                                                           \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " << __LINE__ << ": " << message << std::endl; \
            std::abort();                                                                                                             \
        }                                                                                                                             \
    } while (false)