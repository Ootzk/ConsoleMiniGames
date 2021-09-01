#pragma once
#include "core.h"

class Board2048
{
	friend void draw(Board2048& B);
	using board = std::vector<std::vector<intP>>;

private:
	bool drawed_after_change = false;

	intP size = 4;
	board B = {
		{0, 0, 2, 0},
		{0, 0, 0, 2},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

public:
	Board2048() {};

	void shift(const DIRECTION& dir);
};

void draw(Board2048& B);