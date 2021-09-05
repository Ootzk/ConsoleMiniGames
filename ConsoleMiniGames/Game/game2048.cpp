#include "game2048.h"

Board2048::Board2048() 
{
}

Board2048::Board2048(board b)
	:B(b)
{
}

void Board2048::clear()
{
	B = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
}


std::pair<std::vector<intP>, intP> Board2048::shift(const DIRECTION& dir) {
	// generalized shift
	for (intP i1 = 0; i1 < size; ++i1) {
		for (intP w = 0; w < size; ++w) {
			intP x1 = 0, y1 = 0;
			switch (dir)
			{
			case DIRECTION::LEFT:
				x1 = w;
				y1 = i1;
				break;
			case DIRECTION::RIGHT:
				x1 = size - 1 - w;
				y1 = i1;
				break;
			case DIRECTION::UP:
				x1 = i1;
				y1 = w;
				break;
			case DIRECTION::DOWN:
				x1 = i1;
				y1 = size - 1 - w;
				break;
			default:
				break;
			}
			intP& write = B[y1][x1];
			for (intP i2 = w + 1; i2 < size; ++i2) {
				intP x2 = 0, y2 = 0;
				switch (dir)
				{
				case DIRECTION::LEFT:
					x2 = i2;
					y2 = i1;
					break;
				case DIRECTION::RIGHT:
					x2 = size - 1 - i2;
					y2 = i1;
					break;
				case DIRECTION::UP:
					x2 = i1;
					y2 = i2;
					break;
				case DIRECTION::DOWN:
					x2 = i1;
					y2 = size - 1 - i2;
					break;
				default:
					break;
				}
				intP& watch = B[y2][x2];
				if (watch != 0) {
					if (write == 0) {
						std::swap(write, watch);
					}
					else {
						if (write == watch) {
							write += watch;
							watch = 0;
						}
						break;
					}
				}
			}
		}
	}

	// update statistics
	std::vector<intP> zero_idx;
	intP max_block = 0;
	for (intP y = 0; y < size; ++y) {
		for (intP x = 0; x < size; ++x) {
			intP num_block = B[y][x];
			max_block = std::max(max_block, num_block);
			if (num_block == 0) zero_idx.emplace_back(y * size + x);
		}
	}
	return { zero_idx, max_block };
}

intP Board2048::at(intP x, intP y) const
{
	//no boundary check; believe ya drawer!
	return B[y][x];
}

void Board2048::gen(intP x, intP y, intP v)
{
	assert(B[y][x] == 0);
	B[y][x] = v;
}
