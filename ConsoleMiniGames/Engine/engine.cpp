#include "engine.h"

void Engine::_init()
{
	// Set Window
	SMALL_RECT windowSize = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &windowSize);
	SetConsoleTitle(L"ESCAPE Game");

	// Hide Cursor
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = false;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

void Engine::run()
{
	_init();

	while (true) {
		switch (state)
		{
		case STATE::MAIN:           state = mainScreen->loop(); break;

		case STATE::EXIT: return;
		}
	}
}
