#pragma once
#include "screen.h"

class CreditScreen : public Screen
{
private:
	SCREEN type = SCREEN::CREDIT;
	WALLPAPER wallpaper = {
		"..\\Screen\\creditScreen_text.txt",
		"..\\Screen\\creditScreen_font.txt",
		"..\\Screen\\creditScreen_back.txt"
	};

protected:
	void _init(const MESSAGE& msg) override;
	std::optional<MESSAGE> _input() override;
	void _draw() override;
	std::optional<MESSAGE> _update() override;
	void _exit(const MESSAGE& msg) override;

public:
	MESSAGE loop(const MESSAGE& msg) override;
};