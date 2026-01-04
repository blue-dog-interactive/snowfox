#include <stdio.h>
#include <stdlib.h>

#include "engine.hpp"
#include "display.hpp"

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
}

void engine_state(State state) {
    $state = state;

    if($state == State::Error) engine_error();

    display_state(state);
}

void engine_event(Event event) {
    $event = event;

    if(event == Event::Boot) engine_boot();
    if(event == Event::Kill) engine_kill();

    display_event(event);
}
