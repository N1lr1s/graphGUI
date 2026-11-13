#include <windows.h>
#include "Window.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    Window window;

    if (!window.Create(hInstance, nCmdShow))
        return -1;

    return window.MessageLoop();
}