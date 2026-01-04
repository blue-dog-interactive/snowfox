#include <algorithm>
#include "entity.hpp"

static Registry $registry;

void entity_draw(void) {
    $registry.destroyed.clear();
}

void entity_mode(Mode mode) {
    static Registry cache;
    if(mode == Mode::Play) cache = $registry;
    if(mode == Mode::Edit) $registry = cache;
}

void entity_state(State state) {
    // nothing atm
}

void entity_event(Event event) {
    if(event == Event::Draw) entity_draw();
}

Entity & entity_make(ID id) {

    Entity entity;
    entity.id = ids_generate();
    entity.type = Type::Empty;

    if(id.hi != 0 || id.lo != 0) {
        entity.id = id;
    }

    $registry.entities.push_back(entity);
    return $registry.entities.back();
}

Entity & entity_kill(ID id) {
    auto & entities  = $registry.entities;
    auto & destroyed = $registry.destroyed;

    auto it = std::find_if(
        entities.begin(),
        entities.end(),
        [&](const Entity& x){ return x.id.hi == id.hi && x.id.lo == id.lo; }
    );

    if (it == entities.end()) {
        Entity empty;
        destroyed.push_back(empty);
        return destroyed.back();
    }

    destroyed.push_back(std::move(*it));
    *it = std::move(entities.back());
    entities.pop_back();

    return entities.back();
}

Entity & entity_find(ID id) {
    auto & entities  = $registry.entities;
    auto & destroyed = $registry.destroyed;

    auto it = std::find_if(
        entities.begin(),
        entities.end(),
        [&](const Entity& x){ return x.id.hi == id.hi && x.id.lo == id.lo; }
    );

    if (it == entities.end()) {
        Entity empty;
        destroyed.push_back(empty);
        return destroyed.back();
    }

    return *it;
}
