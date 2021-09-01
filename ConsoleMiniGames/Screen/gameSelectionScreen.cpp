#include "gameSelectionScreen.h"

void GameSelectionScreen::_init()
{
	_clear();

	moveCursor();
	setPalette(COLOR::LIGHTGRAY, COLOR::BLACK);
	std::cout << "\
   #####                                        #####                          \n\
  #     # ###### #      ######  ####  #####    #     #   ##   #    # ######    \n\
  #       #      #      #      #    #   #      #        #  #  ##  ## #         \n\
   #####  #####  #      #####  #        #      #  #### #    # # ## # #####     \n\
        # #      #      #      #        #      #     # ###### #    # #         \n\
  #     # #      #      #      #    #   #      #     # #    # #    # #         \n\
   #####  ###### ###### ######  ####    #       #####  #    # #    # ######    \n";

	setPalette();
	std::cout << "\
                                                                               \n\
                                       2048                                    \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                               return to main screen                           \n\
                                     exit game                                 \n";

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