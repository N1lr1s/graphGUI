#pragma once

#include <Windows.h>

#include "Layout.h"
#include "Controls.h"
#include "Renderer.h"


class Window
{
public:

    Window();

    bool Create(
        HINSTANCE hInstance,
        int nCmdShow);

    int MessageLoop();

private:

    HWND m_hwnd{};


    Layout m_layout;

    Controls m_controls;

	CoordinateSystem m_coord;


    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam);


    LRESULT HandleMessage(
        UINT msg,
        WPARAM wParam,
        LPARAM lParam);
};