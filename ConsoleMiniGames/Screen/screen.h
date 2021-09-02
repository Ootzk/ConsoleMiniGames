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

class Screen
{
protected:
	void _clear();
	void _wait();

	virtual void _init() = 0;
	virtual std::optional<SCREEN> _input() = 0;
	virtual void _draw() = 0;
	virtual std::optional<SCREEN> _update() = 0;
	virtual void _exit() = 0;

public:
	virtual ~Screen();

	virtual SCREEN loop() = 0;
};