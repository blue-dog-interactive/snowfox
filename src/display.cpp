#include <cstddef>
#include <windows.h>
#include <stdio.h>

#include "display.hpp"
#include "opengl.hpp"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")

static WNDCLASS $class   = {};
static HWND     $handle  = {};
static HDC      $device  = {};
static HGLRC    $context = {};

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

    ShowWindow($handle, SW_HIDE);
    UpdateWindow($handle);

    engine_event(Event::Hand);
}

void display_open(void) {
    display_register_class();
    display_handle_create();
}

void display_shut(void) {

    // release dc
    ReleaseDC($handle, $device);

    // delete render context
    wglDeleteContext($context);

    // destory handle
    DestroyWindow($handle);   // destroys all windows of that class
    $handle = nullptr;

    // unregister class
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

    if($context != NULL) {
        if(!IsWindowVisible($handle)) {
            ShowWindow($handle, SW_SHOW);
        }

        glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void display_swap(void) {
    SwapBuffers($device);
}

void display_hand(void) {

    // create device context
    $device = GetDC($handle);
    if (!$device) {
        printf("Failed to create device context!");
        engine_state(State::Error);
        return;
    }

    // create pixel format
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize        = sizeof(pfd);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType   = PFD_TYPE_RGBA;
    pfd.cColorBits   = 32;
    pfd.cAlphaBits   = 8;
    pfd.cDepthBits   = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType   = PFD_MAIN_PLANE;

    int pf = ChoosePixelFormat($device, &pfd);
    if (pf == 0) {
        printf("Failed to create pixel format!");
        engine_state(State::Error);
        return;
    }

    // set pixel format
    if (!SetPixelFormat($device, pf, &pfd)) {
        printf("Failed to select pixel format!");
        engine_state(State::Error);
        return;
    }

    // make context
    $context = wglCreateContext($device);
    if (!$context) {
        printf("Failed to create render context!");
        engine_state(State::Error);
        return;
    }

    // make context current
    if (!wglMakeCurrent($device, $context)) {
        printf("Failed to set render context!");
        engine_state(State::Error);
        return;
    }

    // load opengl functions
    if (!gladLoadGL()) {
        printf("Failed to load glad/opengl functions!");
        engine_state(State::Error);
        return;
    }
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
    if(event == Event::Hand) display_hand();
}
