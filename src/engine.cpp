#include <stdio.h>
#include <stdlib.h>

#include "engine.hpp"
#include "display.hpp"
#include "editor.hpp"
#include "entity.hpp"

static Mode  $mode  = Mode::None;
static State $state = State::None;
static Event $event = Event::None;

void engine_boot(void) {

    // open
    engine_event(Event::Open);

    // loop
    while($state == State::On) {
        engine_event(Event::Draw);
        engine_event(Event::Swap);

        if($mode == Mode::Play) {
            engine_event(Event::Poll);
            // TODO: add tick based on tickerate.
        }
    }

    // shut
    engine_event(Event::Shut);
}

void engine_kill(void) {
    engine_state(State::Off);
}

void engine_error(void) {
    printf("Error\n");
    engine_event(Event::Shut);
    exit(1);
}

void engine_mode(Mode mode) {
    $mode = mode;

    display_mode(mode);
    entity_mode(mode);
    editor_mode(mode);
}

void engine_state(State state) {
    $state = state;

    if($state == State::Error) engine_error();

    display_state(state);
    entity_state(state);
    editor_state(state);
}

void engine_event(Event event) {
    $event = event;

    if(event == Event::Boot) engine_boot();
    if(event == Event::Kill) engine_kill();

    display_event(event);
    entity_event(event);
    editor_event(event);
}
