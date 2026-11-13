#include "Controls.h"

void Controls::Create(HWND hwnd)
{
	m_labelA = CreateWindowW(L"STATIC", L"A:", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, nullptr, nullptr, nullptr);
	m_editA = CreateWindowW(L"EDIT", L"0.0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 0, 0, 0, 0, hwnd, nullptr, nullptr, nullptr);
	m_labelB = CreateWindowW(L"STATIC", L"B:", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, nullptr, nullptr, nullptr);
	m_editB = CreateWindowW(L"EDIT", L"1.0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 0, 0, 0, 0, hwnd, nullptr, nullptr, nullptr);
	m_buttonRun = CreateWindowW(L"BUTTON", L"Запустить", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0, hwnd, (HMENU)ID_BUTTON_RUN, nullptr, nullptr);
}

void Controls::Resize(const RECT& panel)
{
	const int margin = 10;
	const int labelWidth = 20;
	const int editWidth = 100;
	const int buttonWidth = 80;
	const int controlHeight = 25;
	MoveWindow(m_labelA, panel.left + margin, panel.top + margin, labelWidth, controlHeight, TRUE);
	MoveWindow(m_editA, panel.left + margin + labelWidth, panel.top + margin, editWidth, controlHeight, TRUE);
	MoveWindow(m_labelB, panel.left + margin, panel.top + margin * 2 + controlHeight, labelWidth, controlHeight, TRUE);
	MoveWindow(m_editB, panel.left + margin + labelWidth, panel.top + margin * 2 + controlHeight, editWidth, controlHeight, TRUE);
	MoveWindow(m_buttonRun, panel.left + margin, panel.top + margin * 3 + controlHeight * 2, buttonWidth, controlHeight, TRUE);
}

double Controls::GetA() const
{
	wchar_t buffer[64];
	GetWindowTextW(m_editA, buffer, sizeof(buffer) / sizeof(buffer[0]));
	return std::stod(buffer);
}

double Controls::GetB() const
{
	wchar_t buffer[64];
	GetWindowTextW(m_editB, buffer, sizeof(buffer) / sizeof(buffer[0]));
	return std::stod(buffer);
}