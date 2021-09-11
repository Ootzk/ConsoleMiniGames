#pragma once
#include "screen.h"

class GameClearScreen : public Screen
{
private:
	WALLPAPER wallpaper = {
		"..\\Screen\\gameClearScreen_text.txt",
		"..\\Screen\\gameClearScreen_font.txt",
		"..\\Screen\\gameClearScreen_back.txt",
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