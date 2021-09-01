#pragma once
#include "screen.h"

class GameSelectionScreen : public Screen
{
	using Choices = std::unordered_map<SCREEN, Coordinate>;
	using Cursor = Choices::const_iterator;

private:
	Choices choices = {
		{SCREEN::MAIN, Coordinate{14, 26}},
		{SCREEN::EXIT, Coordinate{14, 27}}
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