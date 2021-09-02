#pragma once
#include "core.h"

class Board2048
{
	using board = std::vector<std::vector<intP>>;

private:
	intP movements_ = 0;
	intP maxblock_ = 2;
	intP size_ = 4;
	board B = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	std::mt19937 eng{ std::random_device{} () };
	std::uniform_int_distribution<int> dis{ 0, size_ * size_ - 1 };

private:
	void generate_random_block(int num_blocks=1);

public:
	Board2048();
	void clear();
	void shift(const DIRECTION& dir);
	intP at(intP x, intP y) const;
	intP size() const;
	intP movements();
	intP maxblock();
};