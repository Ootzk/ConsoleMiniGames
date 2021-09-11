#pragma once
#include "screen.h"

class GameOverScreen : public Screen
{
private:
	SCREEN type = SCREEN::GAMEOVER;
	WALLPAPER wallpaper = {
		"..\\Screen\\gameOverScreen_text.txt",
		"..\\Screen\\gameOverScreen_font.txt",
		"..\\Screen\\gameOverScreen_back.txt",
	};

	CHOICES choices = {
		{SCREEN::GAME2048, Coordinate{14, 32}},
		{SCREEN::MAIN,     Coordinate{14, 33}}
	};
	CURSOR current = choices.cbegin();
	CURSOR previous = choices.cbegin();

protected:
	void _init(const MESSAGE& msg) override;
	std::optional<MESSAGE> _input() override;
	void _draw() override;
	std::optional<MESSAGE> _update() override;
	void _exit(const MESSAGE& msg) override;

public:
	MESSAGE loop(const MESSAGE& msg) override;
};