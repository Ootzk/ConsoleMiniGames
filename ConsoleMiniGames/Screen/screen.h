#pragma once
#include "core.h"

enum class SCREEN
{
	MAIN,
	CREDIT,
	GAMESELECT,

	GAME2048,

	GAMECLEAR,
	GAMEOVER,

	EXIT
};

struct MESSAGE
{
	SCREEN from;
	SCREEN to;

	std::vector<std::string> msg;
};

using CHOICES = std::unordered_map<SCREEN, Coordinate>;
using CURSOR = CHOICES::const_iterator;

class Screen
{
protected:
	void _clear();
	void _wait();

	virtual void _init(const MESSAGE& msg) = 0;
	virtual std::optional<MESSAGE> _input() = 0;
	virtual void _draw() = 0;
	virtual std::optional<MESSAGE> _update() = 0;
	virtual void _exit() = 0;

public:
	virtual ~Screen();

	virtual MESSAGE loop(const MESSAGE& msg) = 0;
};