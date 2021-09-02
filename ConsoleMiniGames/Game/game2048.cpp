#include "game2048.h"

Board2048::Board2048() {
	generate_random_block(3);
}


void Board2048::generate_random_block(int num_blocks)
{
	intP x = 0, y = 0;
	for (intP r = 0; r < num_blocks; ++r) {
		bool generated = false;
		while (not generated) {
			intP rand_idx = dis(eng);
			y = rand_idx / size, x = rand_idx % size;
			if (B[y][x] == 0) {
				B[y][x] = 2;
				generated = true;
			}
		}
	}
}


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
	generate_random_block();
}

void draw(Board2048& B)
{
	intP s = 8, e = 2;
	std::unordered_map<intP, WallPaper> sprites = {
		{0, {"../Game/num_0_text.txt", "../Game/num_0_font.txt", "../Game/num_0_back.txt"}},
		{2, {"../Game/num_2_text.txt", "../Game/num_2_font.txt", "../Game/num_2_back.txt"}},
		{4, {"../Game/num_4_text.txt", "../Game/num_4_font.txt", "../Game/num_4_back.txt"}},
		{8, {"../Game/num_8_text.txt", "../Game/num_8_font.txt", "../Game/num_8_back.txt"}},
		{16, {"../Game/num_16_text.txt", "../Game/num_16_font.txt", "../Game/num_16_back.txt"}},
		{32, {"../Game/num_32_text.txt", "../Game/num_32_font.txt", "../Game/num_32_back.txt"}},
		{64, {"../Game/num_64_text.txt", "../Game/num_64_font.txt", "../Game/num_64_back.txt"}},
		{128, {"../Game/num_128_text.txt", "../Game/num_128_font.txt", "../Game/num_128_back.txt"}},
		{256, {"../Game/num_256_text.txt", "../Game/num_256_font.txt", "../Game/num_256_back.txt"}},
		{512, {"../Game/num_512_text.txt", "../Game/num_512_font.txt", "../Game/num_512_back.txt"}},
		{1024, {"../Game/num_1024_text.txt", "../Game/num_1024_font.txt", "../Game/num_1024_back.txt"}},
	};
	
	if (not B.drawed_after_change) {
		for (intP y = 0; y < B.size; ++y) {
			for (intP x = 0; x < B.size; ++x) {
				intP num = B.B[y][x];
				sprites.find(num)->second.draw({ (s + e) * x, (s + e) * y });
			}
		}
	}
	B.drawed_after_change = true;
}
