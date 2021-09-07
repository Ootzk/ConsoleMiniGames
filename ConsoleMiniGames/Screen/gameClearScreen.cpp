#include "gameClearScreen.h"

void GameClearScreen::_init(const MESSAGE& msg)
{
	_clear();
	wallpaper.draw();

    setPalette(COLOR::YELLOW, COLOR::BLACK);
    moveCursor({ 17, 27 });
    for (intP i = 0; i < msg.msg.size(); ++i) {
        std::cout << msg.msg[i];
        Coordinate coord = getCursorLocation();
        moveCursor({ 17, coord.y + 1 });
    }

    setPalette(COLOR::YELLOW, COLOR::BLACK);
	moveCursor(current->second);
	std::cout << ">";
}

std::optional<MESSAGE> GameClearScreen::_input()
{
    KEY key = getKEY();
    switch (key)
    {
    case KEY::SELECT: return MESSAGE{ SCREEN::GAMECLEAR, current->first,  {} };
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

void GameClearScreen::_draw()
{
    if (previous != current) {
        moveCursor(previous->second);
        std::cout << " ";
        moveCursor(current->second);
        std::cout << ">";
        previous = current;
    }
}

std::optional<MESSAGE> GameClearScreen::_update()
{
    std::optional<MESSAGE> maybe = _input();
    _draw();
    _wait();

    return maybe;
}

void GameClearScreen::_exit(const MESSAGE& msg)
{
    current = choices.cbegin();
    previous = choices.cbegin();
}

MESSAGE GameClearScreen::loop(const MESSAGE& msg)
{
    _init(msg);

    std::optional<MESSAGE> maybe = std::nullopt;
    while (!maybe.has_value()) {
        maybe = _update();
    }

    _exit(maybe.value());

    return maybe.value();
}
