#pragma once
#include "screen.h"
#include "game2048.h"

class Game2048Screen : public Screen
{
private:
	WallPaper wallpaper = {
		"../Screen/game2048Screen_text.txt",
		"../Screen/game2048Screen_font.txt",
		"../Screen/game2048Screen_back.txt",
	};
	std::unordered_map<intP, WallPaper> sprites = {
		{0,    {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_0_back.txt"}},
		{2,    {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_2_back.txt"}},
		{4,    {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_4_back.txt"}},
		{8,    {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_8_back.txt"}},
		{16,   {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_16_back.txt"}},
		{32,   {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_32_back.txt"}},
		{64,   {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_64_back.txt"}},
		{128,  {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_128_back.txt"}},
		{256,  {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_256_back.txt"}},
		{512,  {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_512_back.txt"}},
		{1024, {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_1024_back.txt"}},
		{2048, {"../Game/blanktext.txt", "../Game/blankfont.txt", "../Game/num_2048_back.txt"}}
	};
	Board2048 B;
	intP board_size = B.size();

private:
	void _draw(const Board2048& B);


protected:
	void _init() override;
	std::optional<SCREEN> _input() override;
	void _draw() override;
	std::optional<SCREEN> _update() override;
	void _exit() override;

public:
	SCREEN loop() override;
};