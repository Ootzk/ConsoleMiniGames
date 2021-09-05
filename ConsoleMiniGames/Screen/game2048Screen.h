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
	std::unordered_map<intP, WALLPAPER> sprites = {
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

	Board2048 B{ {
		{1024, 1024, 1024, 1024},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	} };

	std::vector<intP> zero_idx = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	intP max_block = 0;
	intP movements = 0;

	std::mt19937 random_engine{ std::random_device{}() };

private:
	void _draw(const Board2048& B);
	bool _gen_random_block(intP num_blocks = 1);

protected:
	void _init(const MESSAGE& msg) override;
	std::optional<MESSAGE> _input() override;
	void _draw() override;
	std::optional<MESSAGE> _update() override;
	void _exit(const MESSAGE& msg) override;

public:
	MESSAGE loop(const MESSAGE& msg) override;
};