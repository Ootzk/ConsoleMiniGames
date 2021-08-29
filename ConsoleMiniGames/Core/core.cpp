#include "core.h"

Coordinate::Coordinate(unsigned int x, unsigned int y) :
	x(x), y(y)
{
}

Coordinate::~Coordinate()
{
}

COORD Coordinate::to_COORD()
{
	COORD consoleCOORD;
	consoleCOORD.X = 2 * x; consoleCOORD.Y = y;
	return consoleCOORD;
}
bool Coordinate::operator==(const Coordinate& other) const
{
	return (x == other.x && y == other.y);
}
bool Coordinate::operator!=(const Coordinate& other) const
{
	return !(*this == other);
}
Coordinate Coordinate::operator+(const Coordinate& other) const
{
	return Coordinate(x + other.x, y + other.y);
}
void moveCursor(Coordinate location)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), location.to_COORD());
}
Coordinate getCursorLocation()
{
	CONSOLE_SCREEN_BUFFER_INFO bufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufInfo);

	Coordinate coordinate;
	coordinate.x = bufInfo.dwCursorPosition.X / 2;
	coordinate.y = bufInfo.dwCursorPosition.Y;
	return coordinate;
}

KEY getKEY()
{
	if (_kbhit()) {
		int key = _getch();
		if (key == 224 || key == 0) { //special key: 2 bytes
			key = _getch();
			switch (key)
			{
			case 72: return KEY::UP;
			case 80: return KEY::DOWN;
			case 75: return KEY::LEFT;
			case 77: return KEY::RIGHT;
			}
		}
		else {
			switch (key)
			{
			case 'w': return KEY::UP;
			case 'W': return KEY::UP;
			case 's': return KEY::DOWN;
			case 'S': return KEY::DOWN;
			case 'a': return KEY::LEFT;
			case 'A': return KEY::LEFT;
			case 'd': return KEY::RIGHT;
			case 'D': return KEY::RIGHT;
			case ' ': return KEY::SELECT;
			case 13:  return KEY::SELECT;
			case 'p': return KEY::PAUSE;
			case 'P': return KEY::PAUSE;
			case 27:  return KEY::PAUSE;
			}
		}
	}
	return KEY::NONE;
}

void setPalette(COLOR foreground, COLOR background)
{
	int colorCode = static_cast<int>(foreground) + static_cast<int>(background) * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}