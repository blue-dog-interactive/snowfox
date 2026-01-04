#include "editor.hpp"
#include "entity.hpp"

static ID id;

void editor_open(void) {
    Entity & ent = entity_make();
    id = ent.id;
    ent.version = 10829812;
}

void editor_shut(void) {
    Entity & ent = entity_find(id);

    if(ent.type != Type::None) {
        printf("entity id %d\n", ent.version);
    }
}

void editor_mode(Mode mode) {

}

void editor_state(State state) {

}

void editor_event(Event event) {
    if(event == Event::Open) editor_open();
    if(event == Event::Shut) editor_shut();
}
