#include "game2048.h"

void Board2048::shift(const DIRECTION& dir) {
	drawed_after_change = false;
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
}

void draw(Board2048& B)
{
	if (not B.drawed_after_change) {
		for (intP y = 0; y < B.size; ++y) {
			for (intP x = 0; x < B.size; ++x) {
				std::cout << std::setfill(' ') << std::setw(5) << B.B[y][x];
			}
			std::cout << endl;
		}
	}
	B.drawed_after_change = true;
}
