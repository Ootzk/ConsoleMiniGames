#pragma once
#include "screen.h"
#include "game2048.h"

class Game2048Screen : public Screen
{
private:
	SCREEN type = SCREEN::GAME2048;
	WALLPAPER wallpaper = {
		"../Screen/game2048Screen_text.txt",
		"../Screen/game2048Screen_font.txt",
		"../Screen/game2048Screen_back.txt",
	};

	Game2048 G;

protected:
	void _init(const MESSAGE& msg) override;
	std::optional<MESSAGE> _input() override;
	void _draw() override;
	std::optional<MESSAGE> _update() override;
	void _exit(const MESSAGE& msg) override;

public:
	MESSAGE loop(const MESSAGE& msg) override;
};