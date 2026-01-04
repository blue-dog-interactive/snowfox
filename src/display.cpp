#include <windows.h>
#include <stdio.h>

#include "display.hpp"
#include "engine.hpp"

#pragma comment(lib, "user32.lib")

static WNDCLASS $class  = {};
static HWND     $handle = {};

LRESULT CALLBACK display_window_procedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        }

        case WM_ERASEBKGND: {
            return 1;
        }

        case WM_SIZE: {
            engine_event(Event::Draw);
            engine_event(Event::Swap);
            return 0;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void display_register_class(void) {
    $class.lpfnWndProc   = display_window_procedure;
    $class.hInstance     = GetModuleHandle(nullptr);
    $class.lpszClassName = "snowfox_display_class";
    $class.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    $class.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

    RegisterClass(&$class);
}

void display_handle_create(void) {
    SetProcessDPIAware();

    $handle = CreateWindowEx(
        0,                       // Optional window styles.
        "snowfox_display_class", // Window class
        "Snowfox Engine",        // Window text
        WS_OVERLAPPEDWINDOW,     // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,

        NULL,                      // Parent window
        NULL,                      // Menu
        GetModuleHandle(nullptr),  // Instance handle
        NULL                       // Additional application data
    );

    if ($handle == NULL) {
        printf("Failed to create display handle!");
        engine_state(State::Error);
        return;
    }

    ShowWindow($handle, SW_SHOW);
    UpdateWindow($handle);
}

void display_open(void) {
    display_register_class();
    display_handle_create();
}

void display_shut(void) {
    DestroyWindow($handle);   // destroys all windows of that class
    $handle = nullptr;

    UnregisterClass("snowfox_display_class", GetModuleHandle(nullptr));
}

void display_draw(void) {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT) {
            engine_state(State::Off);
        }
    }
}

void display_swap(void) {

}

void display_mode(Mode mode) {
    // nothing atm
}

void display_state(State state) {
    // nothing atm
}

void display_event(Event event) {
    if(event == Event::Open) display_open();
    if(event == Event::Shut) display_shut();
    if(event == Event::Draw) display_draw();
    if(event == Event::Swap) display_swap();
}
