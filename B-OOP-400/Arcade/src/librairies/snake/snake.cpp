/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** snake
*/

#include "snake.hpp"

Arcade::snake::snake()
{
    init();
}

Arcade::snake::~snake()
{
}

std::vector<std::shared_ptr<Arcade::Object>> Arcade::snake::Turn(Arcade::Event event)
{
    switch (event) {
        case Arcade::Event::GAME_LEFT:
            if (!_alive)
                return _is_dead();
            _do_movement(LEFT);
            break;
        case Arcade::Event::GAME_RIGHT:
            if (!_alive)
                return  _is_dead();
            _do_movement(RIGHT);
            break;
        case Arcade::Event::GAME_RESTART:
            init();
            break;
        default:
            if (!_alive)
                return _is_dead();
            _do_movement(0);
            break;
    }
    return _return_all_objects();
}

void Arcade::snake::init()
{
    _score = 0;
    _direction = RIGHT;
    _len = 4;
    _alive = true;
    _game.clear();
    _snake.clear();
    for (int i = 0; i < MAP_X; i++) {
        for (int j = 0; j < MAP_Y; j++) {
            if (i == 0 || i == MAP_X - 1 || j == 0 || j == MAP_Y - 1) {
                _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(i, j), Arcade::Type::Rectangle, Arcade::Color::WHITE, WALL));
            } else {
                _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(i, j), Arcade::Type::Rectangle, Arcade::Color::GREEN, GROUND));
            }
        }
    }
    for (int i = 0; i < _len; i++)
        _snake.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X / 2 - i, MAP_Y / 2),Arcade::Type::Rectangle, Arcade::Color::RED, BODY));
    _snake.front()->setAsset(HEADRIGHT);
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X - 3, MAP_Y / 2), Arcade::Type::Rectangle, Arcade::Color::PURPLE, FRUIT));
    _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X + 1, 1), Arcade::Type::Text, Arcade::Color::WHITE, "Score: " + std::to_string(_score)));
}

int Arcade::snake::getScore()
{
    return _score;
}

void Arcade::snake::_move_snake(int x, int y)
{
    int oldX = _snake[0]->getPosition().getX();
    int oldY = _snake[0]->getPosition().getY();

    if (_check_colide(oldX + x, oldY + y)) {
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
    } else {
        _alive = false;
    }
}

void Arcade::snake::_set_direction(int direction)
{
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

void Arcade::snake::_do_movement(int direction)
{
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

bool Arcade::snake::_check_colide(int x, int y)
{
    for (auto &object : _game) {
        if (object->getPosition().getX() == x && object->getPosition().getY() == y) {
            if (object->getColor() == Arcade::Color::WHITE)
                return false;
            if (object->getColor() == Arcade::Color::PURPLE) {
                _score++;
                _len++;
                _snake.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(_snake[_len - 2]->getPosition().getX(), _snake[_len - 2]->getPosition().getY()), Arcade::Type::Rectangle, Arcade::Color::RED, BODY));
                _spawn_fruit(object);
                for (auto &i : _game) {
                    if (i->getColor() == Arcade::Color::WHITE && i->getAsset().find("Score") != std::string::npos)
                        i->setAsset("Score: " + std::to_string(_score));
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

std::vector<std::shared_ptr<Arcade::Object>> Arcade::snake::_is_dead()
{
    if (_alive == false) {
        _game.clear();
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X + 1, MAP_Y / 2), Arcade::Type::Text, Arcade::Color::RED, "You died"));
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X + 1, 0), Arcade::Type::Text, Arcade::Color::WHITE, "Snake"));
        _game.push_back(std::make_shared<Arcade::Object>(Arcade::Object::Position(MAP_X + 1, MAP_Y / 2 + 1), Arcade::Type::Text, Arcade::Color::WHITE, "Score: " + std::to_string(_score)));
    }
    return _game;
}

std::vector<std::shared_ptr<Arcade::Object>> Arcade::snake::_return_all_objects()
{
    std::vector<std::shared_ptr<Arcade::Object>> tmp;
    for (auto &object : _game)
        tmp.push_back(object);
    for (auto &object : _snake)
        tmp.push_back(object);
    return tmp;
}

void Arcade::snake::_spawn_fruit(std::shared_ptr<Arcade::Object> object)
{
    object->setPosition(rand() % (MAP_X - 1), rand() % (MAP_Y - 1));
    for (auto &i : _snake)
        if (i->getPosition().getX() == object->getPosition().getX() && i->getPosition().getY() == object->getPosition().getY())
            _spawn_fruit(object);
    if (object->getPosition().getX() == 0)
        object->setPosition(1, object->getPosition().getY());
    if (object->getPosition().getY() == 0)
        object->setPosition(object->getPosition().getX(), 1);
}

extern "C" Arcade::IGame *entryPointGame()
{
    return (new Arcade::snake());
}