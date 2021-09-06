#include "game2048Screen.h"

void Game2048Screen::_draw(const Board2048& B)
{
	intP s = 8, e = 1;
	for (intP y = 0; y < B.size; ++y) {
		for (intP x = 0; x < B.size; ++x) {
			intP num = B.at(x, y);
			if (generated_idx == y * B.size + x and num == 2) {
				 sprites.find(num + 1)->second.draw({ (s + e) * x + 2, (s + e) * y + 2 });
			}
			else sprites.find(num)->second.draw({ (s + e) * x + 2, (s + e) * y + 2 });
		}
	}
}

bool Game2048Screen::_gen_random_block(intP num_blocks)
{
	for (intP n = 0; n < num_blocks; ++n) {
		if (zero_idx.empty()) return false;

		std::shuffle(zero_idx.begin(), zero_idx.end(), random_engine);
		intP r = zero_idx.back(); zero_idx.pop_back();

		B.gen(r % B.size, r / B.size);
		if (num_blocks == 1) generated_idx = r;
	}
	return true;
}

intP Game2048Screen::_score()
{
	int score = max_block * max_block - movements;
	
	if (score < 0) return 0;
	else return score;
}

void Game2048Screen::_init(const MESSAGE& msg)
{
	if (msg.from != SCREEN::PAUSE) {
		B.clear();
		
		zero_idx = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		_gen_random_block(3);

		shifted = false;
		max_block = 2;
		movements = 0;
	}

	_clear();
	wallpaper.draw();

	moveCursor();
	setPalette();
	_draw(B);
}

std::optional<MESSAGE> Game2048Screen::_input()
{
	KEY key = getKEY();
	switch (key)
	{
	case KEY::UP:
		{std::tie(zero_idx, max_block) = B.shift(DIRECTION::UP); shifted = true; return std::nullopt; }
	case KEY::DOWN:
		{std::tie(zero_idx, max_block) = B.shift(DIRECTION::DOWN); shifted = true; return std::nullopt; }
	case KEY::LEFT:
		{std::tie(zero_idx, max_block) = B.shift(DIRECTION::LEFT); shifted = true; return std::nullopt; }
	case KEY::RIGHT:
		{std::tie(zero_idx, max_block) = B.shift(DIRECTION::RIGHT); shifted = true; return std::nullopt; }
	case KEY::PAUSE:
		return MESSAGE{ type, SCREEN::PAUSE, {} };
	default:
		return std::nullopt;
	}
}

void Game2048Screen::_draw()
{
	moveCursor();
	_draw(B);
	moveCursor({ 23, 40 });
	std::cout << movements;
	moveCursor({ 36, 40 });
	std::cout << max_block;
}

std::optional<MESSAGE> Game2048Screen::_update()
{
	std::optional<MESSAGE> maybe = _input();
	if (shifted) {
		movements++;
		if (not _gen_random_block()) {
			return MESSAGE{ type, SCREEN::GAMEOVER,	{ "Game: 2048", "Score: " + std::to_string(_score())} };
		}
		if (max_block == 2048) {
			_draw();
			return MESSAGE{ type, SCREEN::GAMECLEAR, { "Game: 2048", "Score: " + std::to_string(_score())} };
		}
		shifted = false;
	}
	_draw();
	_wait();

	return maybe;
}

void Game2048Screen::_exit(const MESSAGE& msg)
{
	//always turn to SCREEN::PAUSE; so keep the all state when exit.
}

MESSAGE Game2048Screen::loop(const MESSAGE& msg)
{
	_init(msg);

	std::optional<MESSAGE> maybe = std::nullopt;
	while (!maybe.has_value()) {
		maybe = _update();
	}

	_exit(maybe.value());

	return maybe.value();
}
