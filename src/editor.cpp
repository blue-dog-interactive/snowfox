#include "editor.hpp"
#include "entity.hpp"

void editor_open(void) {
    Entity & ent = entity_make();
}

void editor_shut(void) {
    // nothing atm
}

void editor_mode(Mode mode) {

}

void editor_state(State state) {

}

void editor_event(Event event) {
    if(event == Event::Open) editor_open();
    if(event == Event::Shut) editor_shut();
}
