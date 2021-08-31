#pragma once
#include "screen.h"

class MainScreen : public Screen
{
	using CHOICE = STATE;
	using CHOICES = std::unordered_map<CHOICE, Coordinate>;
	using CURSOR = CHOICES::const_iterator;

private:
	CHOICES choices = {
		{STATE::GAMELEVELSELECT, Coordinate{17, 26}},
		{STATE::CREDIT,          Coordinate{17, 27}},
		{STATE::EXIT,            Coordinate{17, 28}}
	};
	CURSOR current = choices.cbegin();
	CURSOR previous = choices.cbegin();

protected:
	void _init() override;
	std::optional<STATE> _input() override;
	void _draw() override;
	std::optional<STATE> _update() override;
	void _exit() override;

public:
	STATE loop() override;
};

