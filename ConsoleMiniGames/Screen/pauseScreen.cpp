#include "pauseScreen.h"

void PauseScreen::_init(const MESSAGE& msg)
{
	choices.insert({ msg.from, Coordinate{15, 32} });
    current = choices.find(msg.from);

	_clear();
	wallpaper.draw();

	moveCursor(current->second);
	std::cout << ">";
}

std::optional<MESSAGE> PauseScreen::_input()
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

void PauseScreen::_draw()
{
    if (previous != current) {
        moveCursor(previous->second);
        std::cout << " ";
        moveCursor(current->second);
        std::cout << ">";
        previous = current;
    }
}

std::optional<MESSAGE> PauseScreen::_update()
{
    std::optional<MESSAGE> maybe = _input();
    _draw();
    _wait();

    return maybe;
}

void PauseScreen::_exit()
{
    choices.clear();
    choices.insert({ SCREEN::MAIN,  Coordinate{15, 33} });
    current  = choices.cbegin();
    previous = choices.cbegin();
}

MESSAGE PauseScreen::loop(const MESSAGE& msg)
{
    _init(msg);

    std::optional<MESSAGE> maybe = std::nullopt;
    while (!maybe.has_value()) {
        maybe = _update();
    }

    _exit();

    return maybe.value();
}
