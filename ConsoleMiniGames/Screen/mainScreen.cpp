#include "mainScreen.h"

void MainScreen::_init(const MESSAGE& msg)
{
    _clear();
    wallpaper.draw();

    moveCursor(current->second);
    std::cout << ">";
}

std::optional<MESSAGE> MainScreen::_input()
{
    KEY key = getKEY();
    switch (key)
    {
    case KEY::SELECT: return MESSAGE{ type, current->first, {} };
    case KEY::UP: {
        previous = current;

        if (current == choices.cbegin()) current = choices.cend();
        --current;
        return std::nullopt;
    }
    case KEY::DOWN: {
        previous = current;

        ++current;
        if (current == choices.cend()) current = choices.cbegin();
        return std::nullopt;
    }
    default: return std::nullopt;
    }
}

void MainScreen::_draw()
{
    if (previous != current) {
        moveCursor(previous->second);
        std::cout << " ";
        moveCursor(current->second);
        std::cout << ">";
        previous = current;
    }
}

std::optional<MESSAGE> MainScreen::_update()
{
    std::optional<MESSAGE> maybe = _input();
    _draw();
    _wait();

    return maybe;
}

void MainScreen::_exit()
{
    previous = choices.cbegin();
    current = choices.cbegin();
}

MESSAGE MainScreen::loop(const MESSAGE& msg)
{
    _init(msg);

    std::optional<MESSAGE> maybe = std::nullopt;
    while (!maybe.has_value()) {
        maybe = _update();
    }

    _exit();

    return maybe.value();
}
