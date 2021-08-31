#pragma once
#include "core.h"
#include "screens.h"

class Engine
{
private:
	std::unique_ptr<Screen> mainScreen = std::make_unique<MainScreen>();

	void _init();

private:
	STATE state = STATE::MAIN;

public:
	void run();
};