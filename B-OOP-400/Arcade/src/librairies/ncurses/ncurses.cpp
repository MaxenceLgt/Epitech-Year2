/*
** EPITECH PROJECT, 2024
** Arcade [WSL: Ubuntu]
** File description:
** ncurses
*/

#include "ncurses.hpp"

namespace Arcade {

    NCurses::NCurses()
    {
        initscr();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        start_color();
        defineColor();
        curs_set(0);
        refresh();
    }

    NCurses::~NCurses()
    {
        endwin();
    }

    void NCurses::clearWindow()
    {
        wclear(stdscr);
    }

    void NCurses::updateWindow()
    {
        wrefresh(stdscr);
    }

    Event NCurses::getInput()
    {
        int ch = getch();

        refresh();
        switch (ch) {
            case KEY_F(1):
                return (Event::PREV_LIB);
            case KEY_F(2):
                return (Event::NEXT_LIB);
            case KEY_F(3):
                return (Event::PREV_GAME);
            case KEY_F(4):
                return (Event::NEXT_GAME);
            case KEY_F(5):
                return (Event::GAME_RESTART);
            case KEY_F(6):
                return (Event::MENU);
            case KEY_BACKSPACE:
                return (Event::BACKSPACE);
            case '\n':
                return (Event::ENTER);
            case ' ':
                return (Event::SPACE);
            case KEY_UP:
                return (Event::GAME_UP);
            case KEY_DOWN:
                return (Event::GAME_DOWN);
            case KEY_LEFT:
                return (Event::GAME_LEFT);
            case KEY_RIGHT:
                return (Event::GAME_RIGHT);
            case KEY_ESCAPE:
                return (Event::ESCAPE);
            case 'a':
                return (Event::IN_A);
            case 'b':
                return (Event::IN_B);
            case 'c':
                return (Event::IN_C);
            case 'd':
                return (Event::IN_D);
            case 'e':
                return (Event::IN_E);
            case 'f':
                return (Event::IN_F);
            case 'g':
                return (Event::IN_G);
            case 'h':
                return (Event::IN_H);
            case 'i':
                return (Event::IN_I);
            case 'j':
                return (Event::IN_J);
            case 'k':
                return (Event::IN_K);
            case 'l':
                return (Event::IN_L);
            case 'm':
                return (Event::IN_M);
            case 'n':
                return (Event::IN_N);
            case 'o':
                return (Event::IN_O);
            case 'p':
                return (Event::IN_P);
            case 'q':
                return (Event::IN_Q);
            case 'r':
                return (Event::IN_R);
            case 's':
                return (Event::IN_S);
            case 't':
                return (Event::IN_T);
            case 'u':
                return (Event::IN_U);
            case 'v':
                return (Event::IN_V);
            case 'w':
                return (Event::IN_W);
            case 'x':
                return (Event::IN_X);
            case 'y':
                return (Event::IN_Y);
            case 'z':
                return (Event::IN_Z);
            default:
                return (Event::NONE);
        }
    }

    void NCurses::draw(std::shared_ptr<Arcade::Object> object)
    {
        if (object->getType() == Rectangle)
            drawRectangle(object);
        else if (object->getType() == Text)
            drawText(object);
        else if (object->getType() == Circle)
            drawCircle(object);
    }

    void NCurses::drawRectangle(std::shared_ptr<Arcade::Object> object)
    {
        int x = object->getPosition().getX() * WIDTH;
        int y = object->getPosition().getY() * HEIGHT;
        int color = object->getColor();

        attron(COLOR_PAIR(color));
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                mvprintw(y + j, x + i, " ");
            }
        }
        attroff(COLOR_PAIR(color));
    }

    void NCurses::drawCircle(std::shared_ptr<Arcade::Object> object)
    {
        int x = object->getPosition().getX() * WIDTH;
        int y = object->getPosition().getY() * HEIGHT;
        int color = object->getColor();

        attron(COLOR_PAIR(color));
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                mvprintw(y + j, x + i, " ");
            }
        }
        attroff(COLOR_PAIR(color));
    }

    void NCurses::drawText(std::shared_ptr<Arcade::Object> object)
    {
        int x = object->getPosition().getX() * WIDTH;
        int y = object->getPosition().getY() * HEIGHT;
        int color = object->getColor();

        attron(COLOR_PAIR(10 + color));
        mvprintw(y, x, "%s", object->getAsset().c_str());
        attroff(COLOR_PAIR(10 + color));
    }

    void NCurses::defineColor()
    {
        init_pair(0, COLOR_BLACK, COLOR_BLUE);
        init_pair(1, COLOR_BLACK, COLOR_RED);
        init_pair(2, COLOR_BLACK, COLOR_YELLOW);
        init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(4, COLOR_BLACK, COLOR_WHITE);
        init_pair(5, COLOR_BLACK, COLOR_GREEN);
        init_pair(6, COLOR_BLACK, COLOR_WHITE);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
        init_pair(8, COLOR_BLACK, COLOR_WHITE);
        init_pair(10, COLOR_BLUE, COLOR_WHITE);
        init_pair(11, COLOR_RED, COLOR_BLACK);
        init_pair(12, COLOR_YELLOW, COLOR_BLACK);
        init_pair(13, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(14, COLOR_WHITE, COLOR_BLACK);
        init_pair(15, COLOR_GREEN, COLOR_BLACK);
        init_pair(16, COLOR_WHITE, COLOR_BLACK);
        init_pair(17, COLOR_BLACK, COLOR_WHITE);
        init_pair(18, COLOR_WHITE, COLOR_BLACK);
    }

    int NCurses::playTurn()
    {
        float dif = clock() - _clock;
        int result = dif / 500000;

        if (result >= 0.1) {
            _clock = clock();
            return result;
        } 
        return 0;
    }

}

extern "C" Arcade::IDisplay *entryPointDisplay()
{
    return (new Arcade::NCurses());
}
