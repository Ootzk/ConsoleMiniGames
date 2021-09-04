#pragma once
#include "screen.h"

class GameSelectionScreen : public Screen
{
private:
	SCREEN type = SCREEN::GAMESELECT;
	WALLPAPER wallpaper = {
		"../Screen/gameSelectionScreen_text.txt",
		"../Screen/gameSelectionScreen_font.txt",
		"../Screen/gameSelectionScreen_back.txt",
	};
	CHOICES choices = {
		{SCREEN::GAME2048, Coordinate{12, 10}},
		{SCREEN::MAIN,     Coordinate{12, 36}},
		{SCREEN::EXIT,     Coordinate{12, 37}}
	};
	CURSOR current = choices.cbegin();
	CURSOR previous = choices.cbegin();

protected:
	void _init(const MESSAGE& msg) override;
	std::optional<MESSAGE> _input() override;
	void _draw() override;
	std::optional<MESSAGE> _update() override;
	void _exit() override;

public:
	MESSAGE loop(const MESSAGE& msg) override;
};