#include "game2048Screen.h"

void Game2048Screen::_init(const MESSAGE& msg)
{
	if (msg.from != SCREEN::PAUSE) {
		G.clear();
	}

	_clear();
	wallpaper.draw();

	moveCursor();
	setPalette();
	G.draw(true);
}

std::optional<MESSAGE> Game2048Screen::_input()
{
	KEY key = getKEY();
	switch (key)
	{
	case KEY::UP:
		G.shift(DIRECTION::UP); return std::nullopt;
	case KEY::DOWN:
		G.shift(DIRECTION::DOWN); return std::nullopt;
	case KEY::LEFT:
		G.shift(DIRECTION::LEFT); return std::nullopt;
	case KEY::RIGHT:
		G.shift(DIRECTION::RIGHT); return std::nullopt;
	case KEY::PAUSE:
		return MESSAGE{ type, SCREEN::PAUSE, {} };
	default:
		return std::nullopt;
	}
}

void Game2048Screen::_draw()
{
	moveCursor();
	G.draw();

	intP max_block, movements;
	std::tie(max_block, movements) = G.statistics();

	moveCursor({ 23, 40 });
	std::cout << movements;
	moveCursor({ 36, 40 });
	std::cout << max_block;
}

std::optional<MESSAGE> Game2048Screen::_update()
{
	std::optional<MESSAGE> maybe = _input();
	_draw();
	switch (G.state())
	{
	case Game2048State::GAMEOVER:
		return MESSAGE{ type, SCREEN::GAMEOVER,	 { "Game: 2048", "Score: " + std::to_string(G.score())} };
	case Game2048State::GAMECLEAR:
		return MESSAGE{ type, SCREEN::GAMECLEAR, { "Game: 2048", "Score: " + std::to_string(G.score())} };
	case Game2048State::CONTINUE:
		break;
	}
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
