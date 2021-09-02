#pragma once
#include "screen.h"

class MainScreen : public Screen
{
	using Choices = std::unordered_map<SCREEN, Coordinate>;
	using Cursor = Choices::const_iterator;

private:
	WallPaper wallpaper = {
		"../Screen/mainScreen_text.txt",
		"../Screen/mainScreen_font.txt",
		"../Screen/mainScreen_back.txt" 
	};

	Choices choices = {
		{SCREEN::GAMESELECT,      Coordinate{15, 32}},
		{SCREEN::CREDIT,          Coordinate{15, 33}},
		{SCREEN::EXIT,            Coordinate{15, 34}}
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

