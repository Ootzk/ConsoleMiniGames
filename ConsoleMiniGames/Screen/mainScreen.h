#pragma once
#include "screen.h"

class MainScreen : public Screen
{
private:
	SCREEN type = SCREEN::MAIN;
	WALLPAPER wallpaper = {
		"../Screen/mainScreen_text.txt",
		"../Screen/mainScreen_font.txt",
		"../Screen/mainScreen_back.txt" 
	};

	CHOICES choices = {
		{SCREEN::GAMESELECT,      Coordinate{15, 32}},
		{SCREEN::CREDIT,          Coordinate{15, 33}},
		{SCREEN::EXIT,            Coordinate{15, 34}}
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

