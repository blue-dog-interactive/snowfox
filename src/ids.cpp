#include <random>
#include <cstdint>

#include "ids.hpp"

ID ids_generate(void) {
    static thread_local std::mt19937_64 rng{ std::random_device{}() };
    ID id;
    id.hi = rng();
    id.lo = rng();
    return id;
}
