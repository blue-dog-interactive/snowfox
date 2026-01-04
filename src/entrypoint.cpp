#include "entrypoint.hpp"
#include "engine.hpp"

int main(void) {
    engine_mode(Mode::Play);
    engine_state(State::On);
    engine_event(Event::Boot);
}
