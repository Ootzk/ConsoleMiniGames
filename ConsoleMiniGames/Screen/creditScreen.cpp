#include "creditScreen.h"

void CreditScreen::_init(const MESSAGE& msg)
{
	_clear();
    wallpaper.draw();

    moveCursor({ 17, 21 });
    setPalette(COLOR::WHITE, COLOR::LIGHTRED);
    std::cout << VERSION;

    moveCursor();
    setPalette();
}

std::optional<MESSAGE> CreditScreen::_input()
{
    KEY key = getKEY();
    switch (key)
    {
    case KEY::SELECT: return MESSAGE{ type, SCREEN::MAIN, {} };
    default: return std::nullopt;
    }
}

void CreditScreen::_draw()
{
}

std::optional<MESSAGE> CreditScreen::_update()
{
    std::optional<MESSAGE> maybe = _input();
    _draw();
    _wait();

    return maybe;
}

void CreditScreen::_exit(const MESSAGE& msg)
{
}

MESSAGE CreditScreen::loop(const MESSAGE& msg)
{
    _init(msg);

    std::optional<MESSAGE> maybe = std::nullopt;
    while (!maybe.has_value()) {
        maybe = _update();
    }

    _exit(maybe.value());

    return maybe.value();
}