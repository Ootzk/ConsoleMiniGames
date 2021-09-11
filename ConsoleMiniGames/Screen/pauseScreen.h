#pragma once
#include "screen.h"

class PauseScreen : public Screen
{
private:
	SCREEN type = SCREEN::PAUSE;
	WALLPAPER wallpaper = {
		"..\\Screen\\pauseScreen_text.txt",
		"..\\Screen\\pauseScreen_font.txt",
		"..\\Screen\\pauseScreen_back.txt",
	};
	CHOICES choices = {
		{SCREEN::MAIN,  Coordinate{15, 33}},
	};
	CURSOR current  = choices.cbegin();
	CURSOR previous = choices.cbegin();

protected:
	void _init(const MESSAGE& msg) override;
	std::optional<MESSAGE> _input() override;
	void _draw() override;
	std::optional<MESSAGE> _update() override;
	void _exit(const MESSAGE& msg) override;

public:
	MESSAGE loop(const MESSAGE& msg) override;
};