#include "..\Core\core.h"
#include "screen.h"

Screen::~Screen()
{
}

void Screen::_clear()
{
	system("cls");
}

void Screen::_wait()
{
	Sleep(1000 / FPS);
}