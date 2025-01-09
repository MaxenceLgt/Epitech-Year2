/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Menu
*/

#include "Menu.hpp"
#include "Core.hpp"

namespace Arcade {

    Menu::Menu()
    {
        this->getSavedScores();
    }

    Menu::Menu(const Menu &obj)
    {
        this->_gameInUse = obj._gameInUse;
        this->_games = obj._games;
        this->_libInUse = obj._libInUse;
        this->_libs = obj._libs;
        this->_username = obj._username;
        this->_bestScore = obj._bestScore;
    }

    Menu::~Menu()
    {
    }

    void Menu::refreshLib(LibHandler libHandler)
    {
        std::string libFolder = "./lib/";

        for (const auto &entry : std::filesystem::directory_iterator(libFolder)) {
            std::string libName = libFolder + (std::string)entry.path().filename();
            if (libHandler.libIsChecked(this->_libs, libName) || libHandler.libIsChecked(this->_games, libName))
                continue;
            void *handle = libHandler.openLib(libName);
            if (libHandler.isDisplayLib(handle, false)) {
                this->_libs.push_back(libName);
                libHandler.closeLib(handle);
                continue;
            }
            if (libHandler.isGameLib(handle)) {
                this->_games.push_back(libName);
                continue;
            }
        }
    }

    /* --------------------------------------------- DISPLAY ---------------------------------------- */

    std::vector<std::shared_ptr<Arcade::Object>> Arcade::Menu::menuManager(const Event userInput)
    {
        std::vector<std::shared_ptr<Object>> objects;
        Arcade::Object::Position pos(5, 5);

        this->handleUsernameInput(userInput);
        objects.push_back(std::make_shared<Object>(Object(23, 1, Type::Text, Color::WHITE, "Arcade")));
        this->displayLibs(pos, objects);
        this->displayGames(pos, objects);
        this->displayScore(pos, objects);
        objects.push_back(std::make_shared<Object>(Object(pos, Type::Text, Color::WHITE, "Username :")));
        pos.setX(pos.getX() + 5);
        objects.push_back(std::make_shared<Object>(Object(pos, Type::Text, Color::WHITE, this->_username)));
        return objects;
    }

    void Menu::displayLibs(Object::Position &pos, std::vector<std::shared_ptr<Object>> &objects) const
    {
        std::shared_ptr<Object> display = std::make_shared<Object>(Object(1, 5, Type::Text, Color::WHITE, "Display :"));

        objects.push_back(display);
        for (auto displayLib : this->_libs) {
            objects.push_back(std::make_shared<Object>(Object(pos, Arcade::Type::Text,
            displayLib == this->_libInUse ? Arcade::Color::GREEN : Arcade::Color::WHITE, this->getLibName(displayLib))));
            if (pos.getX() + 5 >= 30) {
                pos.setX(display->getPosition().getX() + 5);
                pos.setY(pos.getY() + 2);
            } else {
                pos.setX(pos.getX() + 5);
            }
        }
        pos.setX(1);
        pos.setY(pos.getY() + 3);
    }

    void Menu::displayGames(Object::Position &pos, std::vector<std::shared_ptr<Object>> &objects) const
    {
        std::shared_ptr<Object> game = std::make_shared<Object>(Object(pos, Type::Text, Color::WHITE, "Game :"));

        objects.push_back(game);
        pos.setX(pos.getX() + 4);
        for (auto gameLib : this->_games) {
            objects.push_back(std::make_shared<Object>(Object(pos, Arcade::Type::Text,
            gameLib == this->_gameInUse ? Arcade::Color::GREEN : Arcade::Color::WHITE, this->getLibName(gameLib))));
            if (pos.getX() + 5 >= 30) {
                pos.setX(game->getPosition().getX() + 5);
                pos.setY(pos.getY() + 2);
            } else {
                pos.setX(pos.getX() + 5);
            }
        }
        pos.setX(game->getPosition().getX());
        pos.setY(pos.getY() + 3);
    }

    void Menu::displayScore(Object::Position &pos, std::vector<std::shared_ptr<Object>> &objects) const
    {
        std::shared_ptr<Object> game = std::make_shared<Object>(Object(pos, Type::Text, Color::WHITE, "Best :"));

        objects.push_back(game);
        pos.setX(pos.getX() + 4);
        for (auto pair : this->_bestScore) {
            if (pair.first == this->_gameInUse) {
                std::string userScore = std::get<0>(pair.second) + " - " + std::to_string(std::get<1>(pair.second));
                objects.push_back(std::make_shared<Object>(Object(pos, Arcade::Type::Text, Arcade::Color::WHITE, userScore)));
            }
        }
        pos.setX(1);
        pos.setY(pos.getY() + 3);
    }

    std::string Menu::getLibName(const std::string lib) const
    {
        std::string result = lib;

        if (result.compare(0, 13, "./lib/arcade_") == 0)
            result.replace(0, 13, "");
        if (result.compare(result.length() - 3, 3, ".so") == 0)
            result.replace(result.length() - 3, 3, "");
        return result;
    }

    void Menu::handleUsernameInput(const Event userInput)
    {
        switch (userInput)
        {
            case Event::IN_1:
                this->_username += "1";
                break;
            case Event::IN_2:
                this->_username += "2";
                break;
            case Event::IN_3:
                this->_username += "3";
                break;
            case Event::IN_4:
                this->_username += "4";
                break;
            case Event::IN_5:
                this->_username += "5";
                break;
            case Event::IN_6:
                this->_username += "6";
                break;
            case Event::IN_7:
                this->_username += "7";
                break;
            case Event::IN_8:
                this->_username += "8";
                break;
            case Event::IN_9:
                this->_username += "9";
                break;
            case Event::IN_A:
                this->_username += "a";
                break;
            case Event::IN_B:
                this->_username += "b";
                break;
            case Event::IN_C:
                this->_username += "c";
                break;
                case Event::IN_D:
                this->_username += "d";
                break;
            case Event::IN_E:
                this->_username += "e";
                break;
            case Event::IN_F:
                this->_username += "f";
                break;
            case Event::IN_G:
                this->_username += "g";
                break;
            case Event::IN_H:
                this->_username += "h";
                break;
            case Event::IN_I:
                this->_username += "i";
                break;
            case Event::IN_J:
                this->_username += "j";
                break;
            case Event::IN_K:
                this->_username += "k";
                break;
            case Event::IN_L:
                this->_username += "l";
                break;
            case Event::IN_M:
                this->_username += "m";
                break;
            case Event::IN_N:
                this->_username += "n";
                break;
            case Event::IN_O:
                this->_username += "o";
                break;
            case Event::IN_P:
                this->_username += "p";
                break;
            case Event::IN_Q:
                this->_username += "q";
                break;
            case Event::IN_R:
                this->_username += "r";
                break;
            case Event::IN_S:
                this->_username += "s";
                break;
            case Event::IN_T:
                this->_username += "t";
                break;
            case Event::IN_U:
                this->_username += "u";
                break;
            case Event::IN_V:
                this->_username += "v";
                break;
            case Event::IN_W:
                this->_username += "w";
                break;
            case Event::IN_X:
                this->_username += "x";
                break;
            case Event::IN_Y:
                this->_username += "y";
                break;
            case Event::IN_Z:
                this->_username += "z";
                break;
            case Event::SPACE:
                this->_username += " ";
                break;
            case Event::BACKSPACE:
                if (!this->_username.empty())
                    this->_username.pop_back();
                break;
            default:
                break;
        }
    }

    /* --------------------------------------------- SCORES ---------------------------------------- */

    void Menu::handleScore(const int playerScore)
    {
        for (auto &pair : this->_bestScore) {
            if (pair.first == this->_gameInUse && std::get<1>(pair.second) < playerScore) {
                std::get<0>(pair.second) = this->_username;
                std::get<1>(pair.second) = playerScore;
                return;
            }
        }
        this->_bestScore[this->_gameInUse] = std::make_tuple(this->_username, playerScore);
    }

    void Menu::saveScores() const
    {
        std::ofstream file("./librairies/settings/scores.txt");

        if (file.fail())
            return;
        for (const auto &pair : this->_bestScore)
            file << pair.first << ":" << std::get<0>(pair.second) << ":" << std::get<1>(pair.second) << std::endl;
    }

    void Menu::getSavedScores()
    {
        std::ifstream fileContent("./librairies/settings/scores.txt");
        std::string line;
        std::smatch matches;
        std::regex pattern(R"(([^:]+):([^:]+):([^:]+))");

        if (fileContent.fail())
            return;
        try {
            while (std::getline(fileContent, line)) {
                if (std::regex_search(line, matches, pattern))
                    this->_bestScore[matches[1]] = std::make_tuple(matches[2], std::stoi(matches[3]));
            }
        } catch (std::exception &e) {
            throw Core::CoreError("Menu : score file has been corrupted.");
        }
    }

    /* --------------------------------------------- GET / SET ---------------------------------------- */

    std::list<std::string> Menu::getGameLibs() const
    {
        return this->_games;
    }

    std::list<std::string> Menu::getDisplayLibs() const
    {
        return this->_libs;
    }

    std::string &Menu::getGameInUse()
    {
        return this->_gameInUse;
    }

    std::string &Menu::getDisplayInUse()
    {
        return this->_libInUse;
    }

    std::string Menu::getUsername() const
    {
        return this->_username;
    }

    void Menu::setGameLibs(std::list<std::string> games)
    {
        this->_games = games;
    }

    void Menu::setDisplayLibs(std::list<std::string> displays)
    {
        this->_libs = displays;
    }

    void Menu::setGameInUse(std::string game)
    {
        this->_gameInUse = game;
    }

    void Menu::setDisplayInUse(std::string display)
    {
        this->_libInUse = display;
    }

    void Menu::setUsername(std::string username)
    {
        this->_username = username;
    }

    /* --------------------------------------------- OPERATORS ---------------------------------------- */

    Menu &Menu::operator=(const Menu &obj)
    {
        if (&obj == this)
            return *this;
        this->_gameInUse = obj._gameInUse;
        this->_games = obj._games;
        this->_libInUse = obj._libInUse;
        this->_libs = obj._libs;
        this->_username = obj._username;
        this->_bestScore = obj._bestScore;
        return *this;
    }
}
