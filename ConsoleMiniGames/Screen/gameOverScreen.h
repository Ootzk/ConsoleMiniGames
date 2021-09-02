#pragma once
#include "screen.h"

class GameOverScreen : public Screen
{
	using Choices = std::unordered_map<SCREEN, Coordinate>;
	using Cursor = Choices::const_iterator;

private:
	WallPaper wallpaper = {
		"../Screen/gameOverScreen_text.txt",
		"../Screen/gameOverScreen_font.txt",
		"../Screen/gameOverScreen_back.txt",
	};

	Choices choices = {
		{SCREEN::GAME2048, Coordinate{14, 32}},
		{SCREEN::MAIN,     Coordinate{14, 33}}
	};
	Cursor current = choices.cbegin();
	Cursor previous = choices.cbegin();

protected:
	void _init() override;
	std::optional<SCREEN> _input() override;
	void _draw() override;
	std::optional<SCREEN> _update() override;
	void _exit() override;

public:
	SCREEN loop() override;
};