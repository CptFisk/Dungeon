#pragma once
#include <assert.h>

#define ASSERT_WITH_MESSAGE(condition, message) \
   do { \
      assert(condition && #message); \
   } while (0);
