#pragma once
#include <conio.h>
#include <Windows.h>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <sstream>
#include <variant>
#include <vector>
#include <unordered_map>
#include <utility>

//constants
const double VERSION = 1.1;

const char endl = '\n';

const int WINDOW_WIDTH = 79;
const int WINDOW_HEIGHT = 43;
const int FPS = 60;

//alias
using intP = unsigned int;


//core components and related functions.
struct Coordinate
{
	unsigned int x;
	unsigned int y;

	Coordinate(unsigned int x = 0, unsigned int y = 0);
	~Coordinate();

	COORD to_COORD();
	bool operator==(const Coordinate& other) const;
	bool operator!=(const Coordinate& other) const;
	Coordinate operator+(const Coordinate& other) const;
};
void moveCursor(Coordinate location = { 0, 0 });
Coordinate getCursorLocation();

enum class KEY
{
	UP,     // 'w' / 'W' / 'ก่'
	LEFT,   // 'a' / 'A' / 'ก็'
	DOWN,   // 's' / 'S' / 'ก้'
	RIGHT,  // 'd' / 'D' / 'กๆ'

	SELECT, // SPACE BAR / ENTER
	PAUSE,  // 'p' / 'P' / ESC

	NONE    // no input
};
KEY getKEY();

enum class COLOR
{
	BLACK,       // 'X' (fill all)
	BLUE,        // 'B'
	GREEN,       // 'G'
	CYAN,        // 'C'
	RED,         // 'R'
	PURPLE,      // 'P'
	BROWN,       // 'O' (oak)
	LIGHTGRAY,   // 'a' (ash)
	DARKGRAY,    // 'A'
	LIGHTBLUE,   // 'b'
	LIGHTGREEN,  // 'g'
	LIGHTCYAN,   // 'c'
	LIGHTRED,    // 'r'
	LIGHTPURPLE, // 'p'
	YELLOW,      // 'Y'
	WHITE,       // 'W'

	DEFAULT      // ' ' (WHITE in foreground, BLACK in background)
};
COLOR char2COLOR(char c);

void setPalette(COLOR foreground = COLOR::WHITE, COLOR background = COLOR::BLACK);
void setPalette(int colorCode);

enum class DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

void draw(std::ifstream& text, std::ifstream& font, std::ifstream& back);