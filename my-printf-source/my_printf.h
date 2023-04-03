#ifndef _REAL_PRINTF_HELL_
#define _REAL_PRINTF_HELL_

#include <cstdint>
#include <climits>
#include <memory>
#include <cstdlib>

static std::size_t _placeholder_space = LONG_MAX;  // not used

#define __realign(p, type) std::align(alignof (type), 0, (p), ::_placeholder_space) 

void my_printf(const char* format, void* buffer);

#endif
