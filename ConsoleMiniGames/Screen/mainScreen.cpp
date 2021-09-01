#include "mainScreen.h"

void MainScreen::_init()
{
    //clear the screen
    _clear();

    //draw wallpaper
    moveCursor();
    setPalette(COLOR::LIGHTGREEN, COLOR::BLACK);
    std::cout << "\
                                                                               \n\
                                                                               \n\
                                                                               \n\
                 #####                                                         \n\
                #     #  ####  #    #  ####   ####  #      ######              \n\
                #       #    # ##   # #      #    # #      #                   \n\
                #       #    # # #  #  ####  #    # #      #####               \n\
                #     # #    # #   ## #    # #    # #      #                   \n\
                 #####   ####  #    #  ####   ####  ###### ######              \n";
    setPalette(COLOR::YELLOW, COLOR::BLACK);
    std::cout << "\
                            #     #                                            \n\
                            ##   ##  #  #    #  #                              \n\
                            # # # #  #  ##   #  #                              \n\
                            #  #  #  #  # #  #  #                              \n\
                            #     #  #  #    #  #                              \n";
    setPalette(COLOR::RED, COLOR::BLACK);
    std::cout << "\
                       #####                                                   \n\
                      #     #   ##   #    # ######  ####                       \n\
                      #        #  #  ##  ## #      #                           \n\
                      #  #### #    # # ## # #####   ####                       \n\
                      #     # ###### #    # #           #                      \n\
                       #####  #    # #    # ######  ####                       \n\
                                                                               \n";
    setPalette(COLOR::WHITE, COLOR::BLACK);
    std::cout << "\
                                                                               \n\
                         maker: Ootzk(blitz555@dgist.ac.kr)                    \n";
    setPalette(COLOR::LIGHTRED, COLOR::BLACK);
    std::cout << "\
          move: wasd/¡è¡ç¡é¡æ, select: space/enter, pause: p/esc               \n"; //reduce 4 spaces because arrow keys consumes 2 bytes each.
    setPalette(COLOR::WHITE, COLOR::BLACK);
    std::cout << "\
                                                                               \n\
                                                                               \n\
                                    select game                                \n\
                                    credits                                    \n\
                                    exit game                                  \n\
                                                                               \n\
                                                                               \n\
                                                                               \n";

    setPalette();

    //draw cursor
    moveCursor(current->second);
    std::cout << ">";
}

std::optional<STATE> MainScreen::_input()
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

std::optional<STATE> MainScreen::_update()
{
    std::optional<STATE> maybe = _input();
    _draw();
    _wait();

    return maybe;
}

void MainScreen::_exit()
{
    previous = choices.cbegin();
    current = choices.cbegin();
}

STATE MainScreen::loop()
{
    _init();

    std::optional<STATE> maybe = std::nullopt;
    while (!maybe.has_value()) {
        maybe = _update();
    }

    _exit();

    return maybe.value();
}
