#pragma once
#include <assert.h>
#include <iostream>

// Custom assert macro with a message
#define ASSERT_WITH_MESSAGE(condition, message)                                                       \
    if (condition) {                                                                                  \
        std::cerr << #condition << " " << __FILE__ << " " << __LINE__ << " " << message << std::endl; \
        std::abort();                                                                                 \
    }
