#include <algorithm>
#include "entity.hpp"

static Registry $registry;

void entity_poll(void) {
    for(auto & entity : $registry.entities) {

        if(entity.life == Life::Kill)  entity.life = Life::Dead;
        if(entity.life == Life::Awake) entity.life = Life::Alive;
        if(entity.life == Life::None)  entity.life = Life::Awake;

        if(entity.life == Life::Dead) {
            $registry.entities.erase(
                std::remove(
                    $registry.entities.begin(),
                    $registry.entities.end(),
                    entity
                ),
                $registry.entities.end()
            );
        }
    }
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
    if(event == Event::Poll) entity_poll();
}

Registry & entity_registry() {
    return $registry;
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
    Entity & ent = entity_find(id);
    ent.life = Life::Kill;
    return ent;
}

Entity & entity_find(ID id) {
    auto & entities  = $registry.entities;

    auto it = std::find_if(
        entities.begin(),
        entities.end(),
        [&](const Entity& x){ return x.id == id; }
    );

    if (it == entities.end()) {
        Entity empty;
        empty.life = Life::Dead;
        entities.push_back(empty);
        return entities.back();
    }

    return *it;
}

void entity_save(const std::string path) {

}

void entity_load(const std::string path) {

}
