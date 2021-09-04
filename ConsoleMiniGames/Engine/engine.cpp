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
		switch (msg.to)
		{
		case SCREEN::MAIN:           msg = mainScreen->loop(msg);			break;
		case SCREEN::GAMESELECT:     msg = gameSelectionScreen->loop(msg);	break;
		case SCREEN::CREDIT:         msg = creditScreen->loop(msg);			break;
		case SCREEN::GAME2048:       msg = game2048Screen->loop(msg);		break;
		case SCREEN::GAMEOVER:       msg = gameOverScreen->loop(msg);		break;
		case SCREEN::GAMECLEAR:      msg = gameClearScreen->loop(msg);		break;

		case SCREEN::EXIT: return;
		}
	}
}
