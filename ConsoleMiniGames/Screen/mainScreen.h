#pragma once
#include "screen.h"

class MainScreen : public Screen
{
	using Choices = std::unordered_map<SCREEN, Coordinate>;
	using Cursor = Choices::const_iterator;

private:
	Choices choices = {
		{SCREEN::GAMESELECT,      Coordinate{17, 26}},
		{SCREEN::CREDIT,          Coordinate{17, 27}},
		{SCREEN::EXIT,            Coordinate{17, 28}}
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

