#pragma once
#include "core.h"

class Board2048
{
	using board = std::vector<std::vector<intP>>;

private:
	bool gameover = false;
	intP stat_movements  = 0;
	intP stat_maxblock   = 0;
	intP stat_zeroblocks = 0;
	intP size_ = 4;
	board B = {
		{1024, 1024, 1024, 1024},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
	/*board B = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};*/

	std::mt19937 eng{ std::random_device{} () };
	std::uniform_int_distribution<int> dis{ 0, size_ * size_ - 1 };

private:
	void generate_random_block(int num_blocks=1);
	void update();

public:
	Board2048();
	void clear();
	void shift(const DIRECTION& dir);
	intP at(intP x, intP y) const;
	intP size() const;
	intP get_movements() const;
	intP get_maxblock() const;
	bool is_gameover() const;
};