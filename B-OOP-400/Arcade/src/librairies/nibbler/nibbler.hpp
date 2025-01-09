/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** nibbler
*/

#pragma once

#include "IGame.hpp"
#include <map>

#define FRUIT "librairies/assets/snake/fruit.png"
#define GROUND ""
#define WALL "librairies/assets/snake/wall.png"
#define BODY "librairies/assets/snake/body.png"
#define HEADUP "librairies/assets/snake/head_up.png"
#define HEADDOWN "librairies/assets/snake/head_down.png"
#define HEADLEFT "librairies/assets/snake/head_left.png"
#define HEADRIGHT "librairies/assets/snake/head_right.png"

#define MAP_X 21
#define MAP_Y 21

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

namespace Arcade {
    class nibbler: public Arcade::IGame {
        public:
            nibbler();
            ~nibbler();
            std::vector<std::shared_ptr<Arcade::Object>> Turn(Arcade::Event event);
            void init();
            int getScore();
        private:
            void _generate_map(int i, int j);
            void _move_snake(int direction_x, int direction_y);
            void _do_movement(int direction, bool set_direction);
            void _set_direction(int direction);
            int _check_colide(int x, int y);
            std::vector<std::shared_ptr<Arcade::Object>> _return_all_objects();
            std::vector<std::shared_ptr<Arcade::Object>> _is_dead();
            std::vector<std::shared_ptr<Arcade::Object>> _is_win();
        private:
            int _score;
            std::vector<std::shared_ptr<Arcade::Object>> _game;
            std::vector<std::shared_ptr<Arcade::Object>> _snake;
            int _prev_direction;
            int _direction;
            int _len;
            int _fruit_nb;
            bool _alive;
            bool _lvl_finished;

    };
}
extern "C" Arcade::IGame *entryPointGame();
