#pragma once

enum class Mode {
    None,
    Play,
    Edit,
    Pause
};

enum class State {
    None,
    On,
    Off,
    Error,
};

enum class Event {
    None,
    Boot,
    Kill,
    Open,
    Shut,
    Draw,
    Swap,
    Poll,
    Tick,
};

void engine_mode(Mode mode);
void engine_state(State state);
void engine_event(Event event);
