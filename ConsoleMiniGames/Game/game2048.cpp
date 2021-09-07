#include "game2048.h"

std::unordered_map<intP, WALLPAPER>Game2048::sprites = {
		{0,    {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_0_back.txt"}},
		{2,    {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_2_back.txt"}},
		{3,    {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_3_back.txt"}}, //newly generated '2' block
		{4,    {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_4_back.txt"}},
		{8,    {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_8_back.txt"}},
		{16,   {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_16_back.txt"}},
		{32,   {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_32_back.txt"}},
		{64,   {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_64_back.txt"}},
		{128,  {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_128_back.txt"}},
		{256,  {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_256_back.txt"}},
		{512,  {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_512_back.txt"}},
		{1024, {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_1024_back.txt"}},
		{2048, {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_2048_back.txt"}}
};

Game2048::Game2048()
{
	clear();
}

Game2048::Game2048(const board&& B_init)
	:B_init(B_init)
{
	clear();
}

void Game2048::_generate_random_blocks(const intP num_blocks)
{
	for (intP n = 0; n < num_blocks; ++n) {
		if (zero_idx.empty()) {
			gamestate = Game2048State::GAMEOVER;
			return;
		}

		std::shuffle(zero_idx.begin(), zero_idx.end(), random_engine);
		intP r = zero_idx.back(); zero_idx.pop_back();

		B[r / size][r % size] = 2;
		if (num_blocks == 1) R[r / size][r % size] = REDRAW::G;
	}
}

void Game2048::_shift(const DIRECTION& dir) {
	board B_prev = B;
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

	zero_idx.clear();
	for (intP y = 0; y < size; ++y) {
		for (intP x = 0; x < size; ++x) {
			REDRAW& redraw = R[y][x];
			intP num_block = B[y][x];

			if (B_prev[y][x] != num_block or redraw == REDRAW::G) redraw = REDRAW::O;
			else redraw = REDRAW::X;

			if (num_block == 0) zero_idx.emplace_back(y * size + x);
			max_block = std::max(max_block, num_block);
		}
	}
	movements++;
}

void Game2048::clear()
{
	B = B_init;
	R = {
		{REDRAW::O, REDRAW::O, REDRAW::O, REDRAW::O},
		{REDRAW::O, REDRAW::O, REDRAW::O, REDRAW::O},
		{REDRAW::O, REDRAW::O, REDRAW::O, REDRAW::O},
		{REDRAW::O, REDRAW::O, REDRAW::O, REDRAW::O}
	};
	zero_idx = { 0, 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	_generate_random_blocks(3);
	max_block = 2;
	movements = 0;
	gamestate = Game2048State::CONTINUE;
}

void Game2048::shift(const DIRECTION& dir)
{
	_shift(dir);
	_generate_random_blocks();
}

void Game2048::draw(bool all)
{
	intP s = 8, e = 1;
	for (intP y = 0; y < size; ++y) {
		for (intP x = 0; x < size; ++x) {
			if (all or R[y][x] != REDRAW::X) {
				switch (R[y][x])
				{
				case REDRAW::G:
				{
					sprites.find(B[y][x] + 1)->second.draw({ (s + e) * x + 2, (s + e) * y + 2 });
					break;
				}
				default:
				{
					sprites.find(B[y][x])->second.draw({ (s + e) * x + 2, (s + e) * y + 2 });
					break;
				}
				}
			}
		}
	}
}

std::tuple<intP, intP> Game2048::statistics()
{
	return { max_block, movements };
}

intP Game2048::score()
{
	intP score = max_block * max_block - movements;
	if (score < 0) return 0;
	else return score;
}

Game2048State Game2048::state()
{
	return gamestate;
}