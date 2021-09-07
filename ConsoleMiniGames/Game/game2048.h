#pragma once
#include "core.h"

enum class Game2048State
{
	CONTINUE,
	GAMEOVER,
	GAMECLEAR
};

class Game2048
{
	using board = std::vector<std::vector<intP>>;

	enum class REDRAW
	{
		X,
		O,
		G
	};
	using redraw = std::vector<std::vector<REDRAW>>;

private:
	static std::unordered_map<intP, WALLPAPER> sprites;

	const board B_init{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	};
	board B;
	redraw R;

	std::vector<intP> zero_idx = {0, 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	intP max_block = 0;
	intP movements = 0;

	Game2048State gamestate = Game2048State::CONTINUE;

private:
	void _generate_random_blocks(const intP num_blocks=1);
	void _shift(const DIRECTION& dir);

public:
	Game2048();
	Game2048(const board&& B_init);

	const intP size = 4;

	void clear();
	void shift(const DIRECTION& dir);
	void draw(bool ignore_redraw=false);
	std::tuple<intP, intP> statistics();
	intP score();
	Game2048State state();
};