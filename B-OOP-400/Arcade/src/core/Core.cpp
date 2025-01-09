/*
** EPITECH PROJECT, 2023
** Arcade [WSL: Ubuntu-22.04]
** File description:
** Core.cpp
*/

#include <filesystem>
#include <iostream>
#include "Core.hpp"

/* ----------------------------------- CORE ------------------------------------------ */

Arcade::Core::Core(std::string display)
{
    LibHandler libHandler;

    this->_menu = std::unique_ptr<Menu>(new Menu());
    this->_menu->refreshLib(libHandler);
    this->_menu->setDisplayInUse(display);
    if (this->_menu->getGameLibs().size() != 0)
        this->_menu->setGameInUse(this->_menu->getGameLibs().front());
}

Arcade::Core::Core(const Arcade::Core &obj)
{
    this->_isDisplayMenu = obj._isDisplayMenu;
    this->_isPlaying = obj._isPlaying;
}

Arcade::Core::~Core()
{
}

void Arcade::Core::mainLoop()
{
    LibHandler libManager;
    std::vector<std::shared_ptr<Object>> objects;
    this->_display = std::unique_ptr<IDisplay>(libManager.libLoader<IDisplay>(this->_menu->getDisplayInUse()));
    Arcade::Event lastEvent = Event::NONE;

    while (_isPlaying) {
        Event input = this->_display->getInput();
        if (input != Event::NONE)
            lastEvent = input;
        for (int turnToPlay = this->_display->playTurn(); turnToPlay > 0; turnToPlay--) {
            if (_isDisplayMenu)
                objects = this->_menu->menuManager(lastEvent);
            else {
                objects = this->_game->Turn(lastEvent);
                this->_menu->handleScore(this->_game->getScore());
            }
            this->manageInput(lastEvent, objects);
        }
    }
    this->_menu->saveScores();
}

void Arcade::Core::manageInput(Arcade::Event &userInput, std::vector<std::shared_ptr<Object>> objects)
{
    LibHandler libManager;

    switch (userInput) {
        case Event::NEXT_LIB:
            this->switchNextLib<IDisplay>(this->_menu->getDisplayLibs(), this->_menu->getDisplayInUse(), this->_display);
            break;
        case Event::ENTER:
            if (this->_isDisplayMenu) {
                this->_isDisplayMenu = false;
                this->_game = nullptr;
                this->_game = std::unique_ptr<IGame>(libManager.libLoader<IGame>(this->_menu->getGameInUse()));
            }
            break;
        case Event::NEXT_GAME:
            this->switchNextLib<IGame>(this->_menu->getGameLibs(), this->_menu->getGameInUse(), this->_game);
            break;
        case Event::MENU:
            this->_isDisplayMenu = true;
            break;
        case Event::ESCAPE:
            this->_isPlaying = false;
            break;
        case Event::PREV_GAME:
            this->switchPrevLib<IGame>(this->_menu->getGameLibs(), this->_menu->getGameInUse(), this->_game);
            break;
        case Event::PREV_LIB:
            this->switchPrevLib<IDisplay>(this->_menu->getDisplayLibs(), this->_menu->getDisplayInUse(), this->_display);
            break;
        case Event::REFRESH:
            this->refreshLib();
            break;
        default:
            this->_display.get()->clearWindow();
            for (auto object : objects)
                this->_display.get()->draw(object);
            this->_display.get()->updateWindow();
            break;
        }
        userInput = Event::NONE;
}

void Arcade::Core::refreshLib() const
{
    LibHandler libHandler;

    this->_menu->refreshLib(libHandler);
}

Arcade::Core &Arcade::Core::operator=(const Arcade::Core &obj)
{
    if (&obj == this)
        return *this;
    this->_isDisplayMenu = obj._isDisplayMenu;
    this->_isPlaying = obj._isPlaying;
    return *this;
}
