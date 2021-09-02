#include "game2048.h"

Board2048::Board2048() {
	generate_random_block(3);
}

void Board2048::clear()
{
	B = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
	generate_random_block(3);

	gameover = false;
	stat_movements  = 0;
	stat_maxblock   = 0;
	stat_zeroblocks = 0;
}


void Board2048::generate_random_block(int num_blocks)
{
	intP x = 0, y = 0;
	for (intP r = 0; r < num_blocks; ++r) {
		bool generated = false;
		while (not generated) {
			intP rand_idx = dis(eng);
			y = rand_idx / size_, x = rand_idx % size_;
			if (B[y][x] == 0) {
				B[y][x] = 2;
				generated = true;
			}
		}
	}
}

void Board2048::update()
{
	stat_movements++;
	stat_zeroblocks = 0;
	for (intP y = 0; y < size_; ++y) {
		for (intP x = 0; x < size_; ++x) {
			intP num = B[y][x];
			if (num == 0) stat_zeroblocks++;
			stat_maxblock = std::max(stat_maxblock, num);
		}
	}
	if (stat_zeroblocks == 0) {
		gameover = true;
		return;
	}
	generate_random_block();
}


void Board2048::shift(const DIRECTION& dir) {
	for (intP i1 = 0; i1 < size_; ++i1) {
		for (intP w = 0; w < size_; ++w) {
			intP x1 = 0, y1 = 0;
			switch (dir)
			{
			case DIRECTION::LEFT:
				x1 = w;
				y1 = i1;
				break;
			case DIRECTION::RIGHT:
				x1 = size_ - 1 - w;
				y1 = i1;
				break;
			case DIRECTION::UP:
				x1 = i1;
				y1 = w;
				break;
			case DIRECTION::DOWN:
				x1 = i1;
				y1 = size_ - 1 - w;
				break;
			default:
				break;
			}
			intP& write = B[y1][x1];
			for (intP i2 = w + 1; i2 < size_; ++i2) {
				intP x2 = 0, y2 = 0;
				switch (dir)
				{
				case DIRECTION::LEFT:
					x2 = i2;
					y2 = i1;
					break;
				case DIRECTION::RIGHT:
					x2 = size_ - 1 - i2;
					y2 = i1;
					break;
				case DIRECTION::UP:
					x2 = i1;
					y2 = i2;
					break;
				case DIRECTION::DOWN:
					x2 = i1;
					y2 = size_ - 1 - i2;
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
	update();
}

intP Board2048::at(intP x, intP y) const
{
	//no boundary check; believe ya drawer!
	return B[y][x];
}

intP Board2048::size() const
{
	return size_;
}

intP Board2048::get_movements() const
{
	return stat_movements;
}

intP Board2048::get_maxblock() const
{
	return stat_maxblock;
}

bool Board2048::is_gameover() const
{
	if (gameover) return true;
	else return false;
}
