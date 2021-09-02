#pragma once
#include "core.h"
#include "screens.h"

class Engine
{
private:
	std::unique_ptr<Screen> mainScreen = std::make_unique<MainScreen>();
	std::unique_ptr<Screen> gameSelectionScreen = std::make_unique<GameSelectionScreen>();
	std::unique_ptr<Screen> creditScreen = std::make_unique<CreditScreen>();
	std::unique_ptr<Screen> game2048Screen = std::make_unique<Game2048Screen>();
	std::unique_ptr<Screen> gameOverScreen = std::make_unique<GameOverScreen>();
	std::unique_ptr<Screen> gameClearScreen = std::make_unique<GameClearScreen>();

	void _init();

private:
	SCREEN screen = SCREEN::MAIN;

public:
	void run();
};