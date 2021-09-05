#pragma once
#include "core.h"

class Board2048
{
	using board = std::vector<std::vector<intP>>;

private:
	board B = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

public:
	Board2048();
	Board2048(board b);

	const intP size = 4;

	void clear();
	std::pair<std::vector<intP>, intP> shift(const DIRECTION& dir);
	intP at(intP x, intP y) const;
	void gen(intP x, intP y, intP v = 2);
};