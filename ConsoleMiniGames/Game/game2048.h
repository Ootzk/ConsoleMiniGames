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
		{0, 2, 4, 8},
		{16, 32, 64, 128},
		{256, 512, 1024, 2048},
		{0, 0, 0, 0}
	};
	//board B = {
	//	{0, 0, 0, 0},
	//	{0, 0, 0, 0},
	//	{0, 0, 0, 0},
	//	{0, 0, 0, 0}
	//};

	std::mt19937 eng{ std::random_device{} () };
	std::uniform_int_distribution<int> dis{ 0, size * size - 1 };

private:
	void generate_random_block(int num_blocks=1);

public:
	Board2048();

	void shift(const DIRECTION& dir);
};

void draw(Board2048& B);