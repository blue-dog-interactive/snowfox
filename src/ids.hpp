#pragma once

#include <cstdint>

struct ID {
    uint64_t hi;
    uint64_t lo;
};

ID ids_generate(void);
