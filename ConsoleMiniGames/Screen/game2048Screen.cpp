#include "game2048Screen.h"

void Game2048Screen::_draw(const Board2048& B)
{
	intP s = 8, e = 1;
	for (intP y = 0; y < B.size; ++y) {
		for (intP x = 0; x < B.size; ++x) {
			sprites.find(B.at(x, y))->second.draw({ (s + e) * x + 2, (s + e) * y + 2 });
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
	}
}

void Game2048Screen::_init(const MESSAGE& msg)
{
	if (msg.from != SCREEN::PAUSE) {
		_gen_random_block(3);
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
	case KEY::UP: {
		movements++;
		std::tie(zero_idx, max_block) = B.shift(DIRECTION::UP);
		return std::nullopt;
	}
	case KEY::DOWN: {
		movements++;
		std::tie(zero_idx, max_block) = B.shift(DIRECTION::DOWN);
		return std::nullopt;
	}
	case KEY::LEFT: {
		movements++;
		std::tie(zero_idx, max_block) = B.shift(DIRECTION::LEFT);
		return std::nullopt;
	}
	case KEY::RIGHT: {
		movements++;
		std::tie(zero_idx, max_block) = B.shift(DIRECTION::RIGHT);
		return std::nullopt;
	}
	case KEY::PAUSE:              
		return MESSAGE{ type, SCREEN::PAUSE, {} };
	default: return std::nullopt;
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
	_draw();
	_wait();
	if (max_block == 2048) return MESSAGE{ type, SCREEN::GAMECLEAR,
		{ "Game             : 2048", "Score (max block): " + std::to_string(max_block), "Trial (movements): " + std::to_string(movements)} };
	if (not _gen_random_block()) return MESSAGE{ type, SCREEN::GAMEOVER,
		{ "Game             : 2048", "Score (max block): " + std::to_string(max_block), "Trial (movements): " + std::to_string(movements)} };

	return maybe;
}

void Game2048Screen::_exit(const MESSAGE& msg)
{
	if (msg.to != SCREEN::PAUSE) {
		B.clear();
		zero_idx = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		movements = 0;
		max_block = 0;
	}
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
