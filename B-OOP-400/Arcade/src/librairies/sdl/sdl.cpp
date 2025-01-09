/*
** EPITECH PROJECT, 2024
** Arcade [WSL: Ubuntu]
** File description:
** sdl
*/

#include "sdl.hpp"

namespace Arcade {

    Sdl::Sdl()
    {
        TTF_Init();
        _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
        _surface = SDL_GetWindowSurface(_window);
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    }

    Sdl::~Sdl()
    {
        SDL_DestroyWindow(_window);
        TTF_Quit();
        SDL_Quit();
    }

    Event Sdl::getInput()
    {
        SDL_Event event = {};

        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return (Event::ESCAPE);
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        return (Event::ESCAPE);
                    if (event.key.keysym.sym == SDLK_F1)
                        return (Event::PREV_LIB);
                    if (event.key.keysym.sym == SDLK_F2)
                        return (Event::NEXT_LIB);
                    if (event.key.keysym.sym == SDLK_F3)
                        return (Event::PREV_GAME);
                    if (event.key.keysym.sym == SDLK_F4)
                        return (Event::NEXT_GAME);
                    if (event.key.keysym.sym == SDLK_F5)
                        return (Event::GAME_RESTART);
                    if (event.key.keysym.sym == SDLK_F6)
                        return (Event::MENU);
                    if (event.key.keysym.sym == SDLK_RETURN)
                        return (Event::ENTER);
                    if (event.key.keysym.sym == SDLK_SPACE)
                        return (Event::SPACE);
                    if (event.key.keysym.sym == SDLK_UP)
                        return (Event::GAME_UP);
                    if (event.key.keysym.sym == SDLK_DOWN)
                        return (Event::GAME_DOWN);
                    if (event.key.keysym.sym == SDLK_LEFT)
                        return (Event::GAME_LEFT);
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        return (Event::GAME_RIGHT);
                    if (event.key.keysym.sym == SDLK_a)
                        return (Event::IN_A);
                    if (event.key.keysym.sym == SDLK_b)
                        return (Event::IN_B);
                    if (event.key.keysym.sym == SDLK_c)
                        return (Event::IN_C);
                    if (event.key.keysym.sym == SDLK_d)
                        return (Event::IN_D);
                    if (event.key.keysym.sym == SDLK_e)
                        return (Event::IN_E);
                    if (event.key.keysym.sym == SDLK_f)
                        return (Event::IN_F);
                    if (event.key.keysym.sym == SDLK_g)
                        return (Event::IN_G);
                    if (event.key.keysym.sym == SDLK_h)
                        return (Event::IN_H);
                    if (event.key.keysym.sym == SDLK_i)
                        return (Event::IN_I);
                    if (event.key.keysym.sym == SDLK_j)
                        return (Event::IN_J);
                    if (event.key.keysym.sym == SDLK_k)
                        return (Event::IN_K);
                    if (event.key.keysym.sym == SDLK_l)
                        return (Event::IN_L);
                    if (event.key.keysym.sym == SDLK_m)
                        return (Event::IN_M);
                    if (event.key.keysym.sym == SDLK_n)
                        return (Event::IN_N);
                    if (event.key.keysym.sym == SDLK_o)
                        return (Event::IN_O);
                    if (event.key.keysym.sym == SDLK_p)
                        return (Event::IN_P);
                    if (event.key.keysym.sym == SDLK_q)
                        return (Event::IN_Q);
                    if (event.key.keysym.sym == SDLK_r)
                        return (Event::IN_R);
                    if (event.key.keysym.sym == SDLK_s)
                        return (Event::IN_S);
                    if (event.key.keysym.sym == SDLK_t)
                        return (Event::IN_T);
                    if (event.key.keysym.sym == SDLK_u)
                        return (Event::IN_U);
                    if (event.key.keysym.sym == SDLK_v)
                        return (Event::IN_V);
                    if (event.key.keysym.sym == SDLK_w)
                        return (Event::IN_W);
                    if (event.key.keysym.sym == SDLK_x)
                        return (Event::IN_X);
                    if (event.key.keysym.sym == SDLK_y)
                        return (Event::IN_Y);
                    if (event.key.keysym.sym == SDLK_z)
                        return (Event::IN_Z);
                    if (event.key.keysym.sym == SDLK_BACKSPACE)
                        return (Event::BACKSPACE);
            }
        }
        return (Event::NONE);
    }

    void Sdl::clearWindow()
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
        SDL_RenderClear(_renderer);
    }

    void Sdl::updateWindow()
    {
        SDL_RenderPresent(_renderer);
    }

    void Sdl::draw(std::shared_ptr<Arcade::Object> object)
    {
        if (object->getType() == Rectangle)
            drawRectangle(object);
        else if (object->getType() == Text)
            drawText(object);
        else if (object->getType() == Circle)
            drawCircle(object);
    }

    void Sdl::drawRectangle(std::shared_ptr<Arcade::Object> object)
    {
        SDL_Rect rect;
        rect.x = object->getPosition().getX() * SIZE;
        rect.y = object->getPosition().getY() * SIZE;
        rect.w = SIZE;
        rect.h = SIZE;

        if (!object->getAsset().empty() && IMG_LoadTexture(_renderer, object->getAsset().c_str()) != NULL) {
            _textures[object->getAsset()] = IMG_LoadTexture(_renderer, object->getAsset().c_str());
            SDL_RenderCopy(_renderer, _textures[object->getAsset()], NULL, &rect);
        } else {
            Colors color = object->getColor();
            SDL_SetRenderDrawColor(_renderer, color._r, color._g, color._b, color._a);
            SDL_RenderFillRect(_renderer, &rect);
            SDL_RenderDrawRect(_renderer, &rect);
        }
    }

    void Sdl::drawText(std::shared_ptr<Arcade::Object> object)
    {
        TTF_Font *font = TTF_OpenFont(FONT, 28);
        Colors color = object->getColor();

        if (!font) {
            throw std::runtime_error("Font Error: " + std::string(TTF_GetError()));
        }
        SDL_Surface *surface = TTF_RenderText_Solid(font, (object->getAsset().length() == 0) ? " " : object->getAsset().c_str(), {(Uint8)color._r, (Uint8)color._g, (Uint8)color._b, (Uint8)color._a});
        if (!surface) {
            throw std::runtime_error("Surface Error: " + std::string(TTF_GetError()));
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        if (!texture) {
            throw std::runtime_error("Texture Error: " + std::string(SDL_GetError()));
        }

        SDL_Rect rect;
        rect.x = object->getPosition().getX() * SIZE;
        rect.y = object->getPosition().getY() * SIZE;
        rect.w = surface->w;
        rect.h = surface->h;
        SDL_RenderCopy(_renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }

    void Sdl::drawCircle(std::shared_ptr<Arcade::Object> object)
    {
        Colors color = object->getColor();
        int radius = SIZE / 2;
        int x = object->getPosition().getX() * SIZE;
        int y = object->getPosition().getY() * SIZE;

        SDL_Rect   rect;
        rect.x = object->getPosition().getX() * SIZE;
        rect.y = object->getPosition().getY() * SIZE;
        rect.w = _surface->w;
        rect.h = _surface->h;

        if (object->getAsset().empty()) {
            SDL_RenderCopy(_renderer, _textures[object->getAsset()], NULL, &rect);
        } else {
            SDL_SetRenderDrawColor(_renderer, color._r, color._g, color._b, color._a);
            for (int i = 0; i < radius; i++) {
                for (int j = 0; j < radius; j++) {
                    if (i * i + j * j <= radius * radius) {
                        SDL_RenderDrawPoint(_renderer, x + i, y + j);
                        SDL_RenderDrawPoint(_renderer, x - i, y + j);
                        SDL_RenderDrawPoint(_renderer, x + i, y - j);
                        SDL_RenderDrawPoint(_renderer, x - i, y - j);
                    }
                }
            }
        }
    }


    Sdl::Colors::Colors(Arcade::Color color)
    {
        switch (color) {
            case Arcade::Color::BLACK:
                _r = 0;
                _g = 0;
                _b = 0;
                _a = 255;
                break;
            case Arcade::Color::WHITE:
                _r = 255;
                _g = 255;
                _b = 255;
                _a = 255;
                break;
            case Arcade::Color::RED:
                _r = 255;
                _g = 0;
                _b = 0;
                _a = 255;
                break;
            case Arcade::Color::GREEN:
                _r = 0;
                _g = 255;
                _b = 0;
                _a = 255;
                break;
            case Arcade::Color::BLUE:
                _r = 0;
                _g = 0;
                _b = 255;
                _a = 255;
                break;
            case Arcade::Color::YELLOW:
                _r = 255;
                _g = 255;
                _b = 0;
                _a = 255;
                break;
            case Arcade::Color::PURPLE:
                _r = 255;
                _g = 0;
                _b = 255;
                _a = 255;
                break;
            case Arcade::Color::GREY:
                _r = 0;
                _g = 128;
                _b = 128;
                _a = 128;
                break;
            default:
                _r = 0;
                _g = 0;
                _b = 0;
                _a = 255;
                break;
        }
    }

    int Sdl::playTurn()
    {
        float dif = clock() - _clock;
        int s = dif / 400000;

        if (s >= 0.6f) {
            _clock = clock();
            return static_cast<int>(s / 0.6f);
        }
        return 0;
    }

}

extern "C" Arcade::IDisplay *entryPointDisplay()
{
    return (new Arcade::Sdl());
}
