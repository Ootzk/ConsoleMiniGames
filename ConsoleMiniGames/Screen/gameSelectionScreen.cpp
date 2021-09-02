#include "gameSelectionScreen.h"

void GameSelectionScreen::_init()
{
	_clear();
    wallpaper.draw();

    moveCursor(current->second);
    std::cout << ">";
}

std::optional<SCREEN> GameSelectionScreen::_input()
{
    KEY key = getKEY();
    switch (key)
    {
    case KEY::SELECT: return current->first;
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


void GameSelectionScreen::_draw()
{
    if (previous != current) {
        moveCursor(previous->second);
        std::cout << " ";
        moveCursor(current->second);
        std::cout << ">";
        previous = current;
    }
}

std::optional<SCREEN> GameSelectionScreen::_update()
{
    std::optional<SCREEN> maybe = _input();
    _draw();
    _wait();

    return maybe;
}

void GameSelectionScreen::_exit()
{
    previous = choices.cbegin();
    current = choices.cbegin();
}

SCREEN GameSelectionScreen::loop()
{
    _init();

    std::optional<SCREEN> maybe = std::nullopt;
    while (!maybe.has_value()) {
        maybe = _update();
    }

    _exit();

    return maybe.value();
}