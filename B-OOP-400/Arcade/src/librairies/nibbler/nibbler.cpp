/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** nibbler
*/

#include "nibbler.hpp"

Arcade::nibbler::nibbler()
{
    init();
}

Arcade::nibbler::~nibbler()
{
}

std::vector<std::shared_ptr<Arcade::Object>> Arcade::nibbler::Turn(Arcade::Event event)
{
    if (_fruit_nb == 0)
        _lvl_finished = true;
    switch (event) {
        case Arcade::Event::GAME_LEFT:
            if (!_alive)
                return _is_dead();
            if (_lvl_finished)
                return _is_win();
            _do_movement(LEFT, true);
            break;
        case Arcade::Event::GAME_RIGHT:
            if (!_alive)
                return _is_dead();
            if (_lvl_finished)
                return _is_win();
            _do_movement(RIGHT, true);
            break;
        case Arcade::Event::GAME_RESTART:
            init();
            break;
        default:
            if (!_alive)
                return _is_dead();
            if (_lvl_finished)
                return _is_win();
            _do_movement(0, true);
            break;
    }
    return _return_all_objects();
}

void Arcade::nibbler::_generate_map(int i, int j)
{
    if (i == 0 || i == MAP_X - 1 || j == 0 || j == MAP_Y - 1) {
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(i, j), Arcade::Type::Rectangle, Arcade::Color::WHITE, WALL));
    } else if (((i > 5 && i < 15) && (i != 10)) && (j == 6 || j == 14 || j == 2 || j == 18)) {
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(i, j), Arcade::Type::Rectangle,Arcade::Color::WHITE, WALL));
    } else if (((i > 2 && i < 18) && (i != 7 && i != 13)) && (j == 4 || j == 16)) {
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(i, j), Arcade::Type::Rectangle,Arcade::Color::WHITE, WALL));
    } else if ((i == MAP_X / 2 + 1 || i == MAP_X / 2 - 1 || i == MAP_X / 2 + 2 || i == MAP_X / 2 - 2 ) && (j == MAP_Y / 2 + 1 || j == MAP_Y / 2 - 1 || j == MAP_Y / 2 + 2|| j == MAP_Y / 2 - 2)) {
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(i, j), Arcade::Type::Rectangle,Arcade::Color::WHITE, WALL));
    } else if ((i == MAP_X / 2 + 4 || i == MAP_X / 2 - 4) && (j == MAP_Y / 2 + 3 || j == MAP_Y / 2 - 3 || j == MAP_Y / 2 - 1 || j == MAP_Y / 2 + 1 || j == MAP_Y / 2 + 2 || j == MAP_Y / 2 - 2)) {
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(i, j), Arcade::Type::Rectangle,Arcade::Color::WHITE, WALL));
    } else if ((i == 3 || i == 17 ) && ((j >= 5 && j <= 15)) && (j != 7 && j != 13)) {
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(i, j), Arcade::Type::Rectangle,Arcade::Color::WHITE, WALL));
    } else {
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(i, j), Arcade::Type::Rectangle, Arcade::Color::GREEN, GROUND));
    }
}

void Arcade::nibbler::init()
{
    _score = 0;
    _direction = RIGHT;
    _len = 4;
    _fruit_nb = 0;
    _alive = true;
    _lvl_finished = false;
    _game.clear();
    _snake.clear();
    for (int i = 0; i < MAP_X; i++)
        for (int j = 0; j < MAP_Y; j++)
            _generate_map(i, j);
    for (int i = 0; i < _len; i++)
        _snake.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X / 2 - i, MAP_Y - 2),Arcade::Type::Rectangle, Arcade::Color::RED, BODY));
    _snake.front()->setAsset(HEADRIGHT);

    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X - 3, MAP_Y / 2), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X - 3, MAP_Y - 3), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X - 3, 2), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(2, MAP_Y / 2), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(2, MAP_Y - 3), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(2, 2), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));

    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X / 2, MAP_Y / 2), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X / 2 - 4, MAP_Y / 2), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X / 2 + 4, MAP_Y / 2), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X / 2, MAP_Y / 2 - 4), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X / 2, MAP_Y / 2 + 4), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));

    for (auto &object : _game)
        if (object->getColor() == Arcade::Color::PURPLE)
            _fruit_nb++;

    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X + 1, 0), Arcade::Type::Text, Arcade::Color::WHITE, "Nibbler"));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X + 1, 1), Arcade::Type::Text, Arcade::Color::WHITE, "Fruits: " + std::to_string(_fruit_nb)));
}

int Arcade::nibbler::getScore()
{
    return _score;
}

void Arcade::nibbler::_move_snake(int x, int y)
{
    int oldX = _snake[0]->getPosition().getX();
    int oldY = _snake[0]->getPosition().getY();
    int collide = _check_colide(oldX + x, oldY + y);
    if (collide == true) {
        for (auto &object : _snake) {
            int tmpX = object->getPosition().getX();
            int tmpY = object->getPosition().getY();
            object->setPosition(oldX, oldY);
            oldX = tmpX;
            oldY = tmpY;
        }
        _snake[0]->setPosition(_snake[0]->getPosition().getX() + x, _snake[0]->getPosition().getY() + y);
        switch (_direction) {
            case UP:
                _snake[0]->setAsset(HEADUP);
                break;
            case DOWN:
                _snake[0]->setAsset(HEADDOWN);
                break;
            case LEFT:
                _snake[0]->setAsset(HEADLEFT);
                break;
            case RIGHT:
                _snake[0]->setAsset(HEADRIGHT);
                break;
        }
    } else if (collide == false) {
        _alive = false;
    } else {
        _direction = _prev_direction;
        collide = true;
        if (_direction == UP || _direction == DOWN) {
            if (_check_colide(oldX - 1, oldY) != 2 && _check_colide(oldX + 1, oldY) == 2) {
                collide = false;
                _direction = LEFT;
            } else if (_check_colide(oldX + 1, oldY) != 2 && _check_colide(oldX - 1, oldY) == 2) {
                collide = false;
                _direction = RIGHT;
            }
        } else if (_direction == LEFT || _direction == RIGHT) {
            if (_check_colide(oldX, oldY - 1) != 2 && _check_colide(oldX, oldY + 1) == 2) {
                collide = false;
                _direction = UP;
            } else if (_check_colide(oldX, oldY + 1) != 2 && _check_colide(oldX, oldY - 1) == 2) {
                collide = false;
                _direction = DOWN;
            }
        }
        if (!collide)
            _do_movement(0, false);
    }
}

void Arcade::nibbler::_set_direction(int direction)
{
    _prev_direction = _direction;
    switch (_direction) {
        case LEFT:
            if (direction == LEFT)
                _direction = DOWN;
            if (direction == RIGHT)
                _direction = UP;
            break;
        case RIGHT:
            if (direction == LEFT)
                _direction = UP;
            if (direction == RIGHT)
                _direction = DOWN;
            break;
        case UP:
            if (direction == LEFT)
                _direction = LEFT;
            if (direction == RIGHT)
                _direction = RIGHT;
            break;
        case DOWN:
            if (direction == LEFT)
                _direction = RIGHT;
            if (direction == RIGHT)
                _direction = LEFT;
            break;
        default:
            break;
    }
}

void Arcade::nibbler::_do_movement(int direction, bool set_direction)
{
    if (set_direction)
        _set_direction(direction);
    switch (_direction) {
        case UP:
            _move_snake(0, -1);
            break;
        case DOWN:
            _move_snake(0, 1);
            break;
        case LEFT:
            _move_snake(-1, 0);
            break;
        case RIGHT:
            _move_snake(1, 0);
            break;
    }
}

int Arcade::nibbler::_check_colide(int x, int y)
{
    for (auto &object : _game) {
        if (object->getPosition().getX() == x && object->getPosition().getY() == y) {
            if (object->getColor() == Arcade::Color::WHITE)
                return 2;
            if (object->getColor() == Arcade::Color::PURPLE) {
                _score++;
                _len++;
                _fruit_nb--;
                _snake.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(_snake[_len - 2]->getPosition().getX(), _snake[_len - 2]->getPosition().getY()), Arcade::Type::Rectangle, Arcade::Color::RED, BODY));
                object->setAsset(GROUND);
                object->setColor(Arcade::Color::GREEN);
                for (auto &i : _game) {
                    if (i->getColor() == Arcade::Color::WHITE && i->getAsset().find("Fruits") != std::string::npos)
                        i->setAsset("Fruits: " + std::to_string(_fruit_nb));
                }
            }
        }
    }
    for (auto &object : _snake) {
        if (object->getPosition().getX() == x && object->getPosition().getY() == y)
            return false;
    }
    return true;
}

std::vector<std::shared_ptr<Arcade::Object>> Arcade::nibbler::_is_dead()
{
    if (!_alive) {
        _game.clear();
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X + 1, MAP_Y / 2), Arcade::Type::Text, Arcade::Color::RED, "You died"));
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X + 1, MAP_Y / 2 + 1), Arcade::Type::Text, Arcade::Color::WHITE, "Score: " + std::to_string(_score)));
    }
    return _game;
}

std::vector<std::shared_ptr<Arcade::Object>> Arcade::nibbler::_is_win()
{
    if (_lvl_finished) {
        _game.clear();
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X + 1, MAP_Y / 2), Arcade::Type::Text, Arcade::Color::GREEN, "You win"));
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X + 1, MAP_Y / 2 + 1), Arcade::Type::Text, Arcade::Color::WHITE, "Score: " + std::to_string(_score)));
    }
    return _game;
}

std::vector<std::shared_ptr<Arcade::Object>> Arcade::nibbler::_return_all_objects()
{
    std::vector<std::shared_ptr<Arcade::Object>> tmp;
    for (auto &object : _game)
        tmp.push_back(object);
    for (auto &object : _snake)
        tmp.push_back(object);
    return tmp;
}

extern "C" Arcade::IGame *entryPointGame()
{
    return (new Arcade::nibbler());
}