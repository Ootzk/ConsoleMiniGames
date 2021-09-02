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

COLOR char2COLOR(char c)
{
	switch(c)
	{
		case 'X': return COLOR::BLACK;
		case 'B': return COLOR::BLUE;
		case 'G': return COLOR::GREEN;
		case 'C': return COLOR::CYAN;
		case 'R': return COLOR::RED;
		case 'P': return COLOR::PURPLE;
		case 'O': return COLOR::BROWN;
		case 'a': return COLOR::LIGHTGRAY;
		case 'A': return COLOR::DARKGRAY;
		case 'b': return COLOR::LIGHTBLUE;
		case 'g': return COLOR::LIGHTGREEN;
		case 'c': return COLOR::LIGHTCYAN;
		case 'r': return COLOR::LIGHTRED;
		case 'p': return COLOR::LIGHTPURPLE;
		case 'Y': return COLOR::YELLOW;
		case 'W': return COLOR::WHITE;
		default: return COLOR::DEFAULT;
	}
}

void setPalette(COLOR foreground, COLOR background)
{
	if (foreground == COLOR::DEFAULT) foreground = COLOR::WHITE;
	if (background == COLOR::DEFAULT) background = COLOR::BLACK;
	int colorCode = static_cast<int>(foreground) + static_cast<int>(background) * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

void setPalette(int colorCode)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

void draw(std::ifstream& text, std::ifstream& font, std::ifstream& back)
{
	if (text.is_open() and font.is_open() and back.is_open()) {
		char T, F, B, f = ' ', b = ' ';
		while (not text.eof() and not font.eof() and not back.eof()) {
			text.get(T); font.get(F); back.get(B);
			if (f != F or b != B) {
				if (T == ' ' and b == B) {
					std::cout << T;
					b = B;
				}
				else {
					setPalette(char2COLOR(F), char2COLOR(B));
					std::cout << T;
					f = F; b = B;
				}
			}
			else {
				std::cout << T;
			}
		}
		setPalette();
		text.close(); font.close(); back.close();
	}
}
