#pragma once
#include "core.h"
#include "screens.h"

class Engine
{
private:
	std::unique_ptr<Screen> mainScreen = std::make_unique<MainScreen>();
	std::unique_ptr<Screen> gameSelectionScreen = std::make_unique<GameSelectionScreen>();

	void _init();

private:
	SCREEN screen = SCREEN::MAIN;

public:
	void run();
};