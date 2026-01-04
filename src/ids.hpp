#pragma once

#include <cstdint>

struct ID {
    uint64_t hi;
    uint64_t lo;
};

inline bool operator==(const ID & a, const ID & b) {
    return a.hi == b.hi && a.lo == b.lo;
}

ID ids_generate(void);
