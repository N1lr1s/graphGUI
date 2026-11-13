#pragma once

#include <Windows.h>
#include <string>

#include "ControlIDs.h"

class Controls
{
public:

    void Create(HWND hwnd);

    void Resize(const RECT& panel);

    double GetA() const;
    double GetB() const;

private:

    HWND m_labelA{};
    HWND m_labelB{};

    HWND m_editA{};
    HWND m_editB{};

    HWND m_buttonRun{};
};
