#include "game2048Screen.h"

void Game2048Screen::_init()
{
	_clear();

	moveCursor();
	setPalette();
	draw(B);
}

std::optional<SCREEN> Game2048Screen::_input()
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
	draw(B);
}

std::optional<SCREEN> Game2048Screen::_update()
{
	std::optional<SCREEN> maybe = _input();
	_draw();
	_wait();

	return maybe;
}

void Game2048Screen::_exit()
{
}

SCREEN Game2048Screen::loop()
{
	_init();

	std::optional<SCREEN> maybe = std::nullopt;
	while (!maybe.has_value()) {
		maybe = _update();
	}

	_exit();

	return maybe.value();
}
