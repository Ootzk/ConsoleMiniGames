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
	enum class CellDrawState
	{
		X,
		O,
	};
	struct Cell
	{
		intP n = 0;
		CellDrawState state = CellDrawState::O;
	};
	using board = std::vector<std::vector<Cell>>;

private:
	static std::unordered_map<intP, WALLPAPER> sprites;
	
	const board B_init{
		{{}, {}, {}, {}},
		{{}, {}, {}, {}},
		{{}, {}, {}, {}},
		{{}, {}, {}, {}}
	};
	board B;

	bool redraw;
	std::vector<intP> zero_idxes;
	intP generated_idx;
	
	intP max_block;
	intP movements;

	Game2048State gamestate = Game2048State::CONTINUE;

private:
	void _generate_random_blocks(const intP num_blocks=1);
	void _shift(const DIRECTION& dir);

public:
	Game2048();
	Game2048(const board&& B_init);

	const intP size = 4;

	void clear();
	void pause();
	void shift(const DIRECTION& dir);
	void draw();
	std::tuple<intP, intP> statistics();
	intP score();
	Game2048State state();
};