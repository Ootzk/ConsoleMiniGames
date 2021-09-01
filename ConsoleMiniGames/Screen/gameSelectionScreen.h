#pragma once
#include "screen.h"

class GameSelectionScreen : public Screen
{
	using Choices = std::unordered_map<STATE, Coordinate>;
	using Cursor = Choices::const_iterator;

private:
	Choices choices = {
		{STATE::MAIN, Coordinate{14, 26}},
		{STATE::EXIT, Coordinate{14, 27}}
	};
	Cursor current = choices.cbegin();
	Cursor previous = choices.cbegin();

protected:
	void _init() override;
	std::optional<STATE> _input() override;
	void _draw() override;
	std::optional<STATE> _update() override;
	void _exit() override;

public:
	STATE loop() override;
};