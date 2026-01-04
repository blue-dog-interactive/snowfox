#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "ids.hpp"
#include "engine.hpp"

enum class Type {
    None,
    Empty,
};

enum class Life {
    None,
    Awake,
    Alive,
    Kill,
    Dead
};

struct Entity {
    ID   id      = {};
    int  version = 1;
    Life life    = Life::None;
    Type type    = Type::None;

    // common
    // vec3 position
    // vec3 rotation
    // vec3 scale
};

inline bool operator==(const Entity& a, const Entity& b) {
    return a.id == b.id;
}

struct Registry {
    std::vector<Entity> entities;
};

void entity_mode(Mode mode);
void entity_state(State state);
void entity_event(Event event);

Registry & entity_registry();

Entity & entity_make(ID id = {});
Entity & entity_kill(ID id = {});
Entity & entity_find(ID id = {});

void entity_save(const std::string path);
void entity_load(const std::string path);
