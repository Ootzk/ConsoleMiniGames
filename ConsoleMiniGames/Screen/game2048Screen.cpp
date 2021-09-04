#include "game2048Screen.h"

void Game2048Screen::_draw(const Board2048& B)
{
	intP s = 8, e = 1;
	for (intP y = 0; y < board_size; ++y) {
		for (intP x = 0; x < board_size; ++x) {
			sprites.find(B.at(x, y))->second.draw({ (s + e) * x + 2, (s + e) * y + 2 });
		}
	}
}

void Game2048Screen::_init(const MESSAGE& msg)
{
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
		B.shift(DIRECTION::UP); return std::nullopt;
	case KEY::DOWN:
		B.shift(DIRECTION::DOWN); return std::nullopt;
	case KEY::LEFT:
		B.shift(DIRECTION::LEFT); return std::nullopt;
	case KEY::RIGHT:
		B.shift(DIRECTION::RIGHT); return std::nullopt;
	default: return std::nullopt;
	}
}

void Game2048Screen::_draw()
{
	moveCursor();
	_draw(B);
	moveCursor({ 23, 40 });
	std::cout << B.get_movements();
	moveCursor({ 36, 40 });
	std::cout << B.get_maxblock();
}

std::optional<MESSAGE> Game2048Screen::_update()
{
	std::optional<MESSAGE> maybe = _input();
	_draw();
	_wait();
	if (B.get_maxblock() == 2048) return MESSAGE{ type, SCREEN::GAMECLEAR,
		{ "Game             : 2048", "Score (max block): " + std::to_string(B.get_maxblock()), "Trial (movements): " + std::to_string(B.get_movements())}};
	if (B.is_gameover())          return MESSAGE{ type, SCREEN::GAMEOVER, 
		{ "Game             : 2048", "Score (max block): " + std::to_string(B.get_maxblock()), "Trial (movements): " + std::to_string(B.get_movements())}};

	return maybe;
}

void Game2048Screen::_exit()
{
	B.clear();
}

MESSAGE Game2048Screen::loop(const MESSAGE& msg)
{
	_init(msg);

	std::optional<MESSAGE> maybe = std::nullopt;
	while (!maybe.has_value()) {
		maybe = _update();
	}

	_exit();

	return maybe.value();
}
