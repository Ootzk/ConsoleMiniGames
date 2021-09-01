#pragma once
#include "screen.h"
#include "game2048.h"

class Game2048Screen : public Screen
{
private:
	Board2048 B;

protected:
	void _init() override;
	std::optional<SCREEN> _input() override;
	void _draw() override;
	std::optional<SCREEN> _update() override;
	void _exit() override;

public:
	SCREEN loop() override;
};