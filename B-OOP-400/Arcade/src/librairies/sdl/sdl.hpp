/*
** EPITECH PROJECT, 2024
** Arcade [WSL: Ubuntu]
** File description:
** sdl
*/

#pragma once
    #include <iostream>
    #include <memory>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <IDisplay.hpp>
    #include <Event.hpp>
    #include <unistd.h>
    #include <unordered_map>

    #define FONT "librairies/assets/arial.ttf"
    #define SIZE 40


namespace Arcade {
    class Sdl : public Arcade::IDisplay {
        public:
            Sdl();
            ~Sdl();

        public:
            Arcade::Event getInput() override;
            void clearWindow() override;
            void updateWindow() override;
            void draw(std::shared_ptr<Arcade::Object> object) override;
            int playTurn() override;

        private:
            class Colors {
                public:
                    Colors() : _r(0), _g(0), _b(0), _a(0) {};
                    Colors(Arcade::Color);
                    Colors(int r, int g, int b, int a) : _r(r), _g(g), _b(b), _a(a) {};
                    ~Colors() = default;
                    int _r;
                    int _g;
                    int _b;
                    int _a;
            };

            void drawRectangle(const std::shared_ptr<Arcade::Object> object) override;
            void drawCircle(const std::shared_ptr<Arcade::Object> object) override;
            void drawText(const std::shared_ptr<Arcade::Object> object) override;
            void defineColor();
            SDL_Window *_window;
            SDL_Surface *_surface;
            SDL_Renderer *_renderer;
            clock_t _clock = clock();
            std::unordered_map<std::string, SDL_Texture *> _textures;
    };
}

extern "C" Arcade::IDisplay *entryPointDisplay();
