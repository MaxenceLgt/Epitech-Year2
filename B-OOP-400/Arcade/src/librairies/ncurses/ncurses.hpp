/*
** EPITECH PROJECT, 2024
** Arcade [WSL: Ubuntu]
** File description:
** NCurses
*/

#pragma once
    #include <iostream>
    #include <memory>
    #include <IDisplay.hpp>
    #include <Event.hpp>
    #include <unistd.h>
    #include <ncurses.h>

    #define WIDTH 4
    #define HEIGHT (WIDTH / 2)
    #define KEY_ESCAPE 27
    #define SIZE 1

namespace Arcade {
    class NCurses : public Arcade::IDisplay {
        public:
            NCurses();
            ~NCurses();

        public:
            Arcade::Event getInput() override;
            void clearWindow() override;
            void updateWindow() override;
            void draw(std::shared_ptr<Arcade::Object> object) override;
            int playTurn() override;

        private:
            void drawRectangle(const std::shared_ptr<Arcade::Object> object) override;
            void drawCircle(const std::shared_ptr<Arcade::Object> object) override;
            void drawText(const std::shared_ptr<Arcade::Object> object) override;
            void defineColor();
            clock_t _clock = clock();
    };
}

extern "C" Arcade::IDisplay *entryPointDisplay();
