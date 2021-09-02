#pragma once
#include "screen.h"

class GameSelectionScreen : public Screen
{
	using Choices = std::unordered_map<SCREEN, Coordinate>;
	using Cursor = Choices::const_iterator;

private:
	WallPaper wallpaper = {
		"../Screen/gameSelectionScreen_text.txt",
		"../Screen/gameSelectionScreen_font.txt",
		"../Screen/gameSelectionScreen_back.txt",
	};

	Choices choices = {
		{SCREEN::GAME2048, Coordinate{12, 10}},
		{SCREEN::MAIN,     Coordinate{12, 36}},
		{SCREEN::EXIT,     Coordinate{12, 37}}
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