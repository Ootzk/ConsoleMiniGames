#include "engine.h"

void Engine::_init()
{
	// Set Window
	SMALL_RECT windowSize = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &windowSize);
	SetConsoleTitle(L"Console Mini Games!");

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
		switch (screen)
		{
		case SCREEN::MAIN:           screen = mainScreen->loop(); break;
		case SCREEN::GAMESELECT:     screen = gameSelectionScreen->loop(); break;
		case SCREEN::CREDIT:         screen = creditScreen->loop(); break;
		case SCREEN::GAME2048:       screen = game2048Screen->loop(); break;

		case SCREEN::EXIT: return;
		}
	}
}
