#pragma once

#include <cstdint>
#include <vector>

#include "ids.hpp"
#include "engine.hpp"

enum class Type {
    None,
    Empty,
};

struct Entity {
    int  version = 1;
    Type type    = Type::None;
    ID   id      = {};

    // common
    // vec3 position
    // vec3 rotation
    // vec3 scale
};

struct Registry {
    std::vector<Entity> entities;
    std::vector<Entity> destroyed;
};

void entity_mode(Mode mode);
void entity_state(State state);
void entity_event(Event event);

Entity & entity_make(ID id = {});
Entity & entity_kill(ID id = {});
Entity & entity_find(ID id = {});
