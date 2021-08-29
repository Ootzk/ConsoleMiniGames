#pragma once
#include "core.h"

class Screen
{
protected:
	void _clear();
	void _wait();

	virtual void _init() = 0;
	virtual std::optional<STATE> _input() = 0;
	virtual void _draw() = 0;
	virtual std::optional<STATE> _update() = 0;
	virtual void _exit() = 0;

public:
	virtual ~Screen();

	virtual STATE loop() = 0;
};