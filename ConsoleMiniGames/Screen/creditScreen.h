#pragma once
#include "screen.h"

class CreditScreen : public Screen
{
	WallPaper wallpaper = {
		"../Screen/creditScreen_text.txt",
		"../Screen/creditScreen_font.txt",
		"../Screen/creditScreen_back.txt"
	};

protected:
	void _init() override;
	std::optional<SCREEN> _input() override;
	void _draw() override;
	std::optional<SCREEN> _update() override;
	void _exit() override;

public:
	SCREEN loop() override;
};