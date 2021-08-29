#pragma once
#include <conio.h>
#include <Windows.h>
#include <cassert>
#include <chrono>
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
const char endl = '\n';

const int WINDOW_WIDTH = 79;
const int WINDOW_HEIGHT = 43;
const int FPS = 60;

enum class STATE
{
	TITLE,
	CREDIT,

	GAMELEVELSELECT,
	GAMEPLAY,
	GAMEOVER,
	GAMECOMPLETE,
	GAMEPAUSE,

	EXIT
};


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
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTPURPLE,
	YELLOW,
	WHITE
};
void setPalette(COLOR foreground = COLOR::WHITE, COLOR background = COLOR::BLACK);