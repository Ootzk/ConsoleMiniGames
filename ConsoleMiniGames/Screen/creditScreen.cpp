#include "creditScreen.h"

void CreditScreen::_init()
{
	_clear();
    wallpaper.draw();

    moveCursor({ 17, 21 });
    setPalette(COLOR::WHITE, COLOR::LIGHTRED);
    std::cout << VERSION;

    moveCursor();
    setPalette();
}

std::optional<SCREEN> CreditScreen::_input()
{
    KEY key = getKEY();
    switch (key)
    {
    case KEY::SELECT: return SCREEN::MAIN;
    default: return std::nullopt;
    }
}

void CreditScreen::_draw()
{
}

std::optional<SCREEN> CreditScreen::_update()
{
    std::optional<SCREEN> maybe = _input();
    _draw();
    _wait();

    return maybe;
}

void CreditScreen::_exit()
{
}

SCREEN CreditScreen::loop()
{
    _init();

    std::optional<SCREEN> maybe = std::nullopt;
    while (!maybe.has_value()) {
        maybe = _update();
    }

    _exit();

    return maybe.value();
}