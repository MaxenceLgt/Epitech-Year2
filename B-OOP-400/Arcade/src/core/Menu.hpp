/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Menu
*/

#pragma once

    #include <memory>
    #include <string>
    #include <vector>
    #include <list>
    #include <fstream>
    #include <sstream>
    #include <regex>
    #include <filesystem>
    #include <map>
    #include <tuple>
    #include "Object.hpp"
    #include "Event.hpp"
    #include "LibHandler.hpp"

namespace Arcade {
    class Menu {
        public:
            Menu();
            Menu(const Menu &obj);
            ~Menu();
        public:
            void refreshLib(LibHandler libHandler);
            std::vector<std::shared_ptr<Object>> menuManager(const Event userInput);
            void displayLibs(Object::Position &pos, std::vector<std::shared_ptr<Object>> &objects) const;
            void displayGames(Object::Position &pos, std::vector<std::shared_ptr<Object>> &objects) const;
            void displayScore(Object::Position &pos, std::vector<std::shared_ptr<Object>> &objects) const;
            std::string getLibName(const std::string lib) const;
            void handleUsernameInput(const Event userInput);
            void handleScore(const int playerScore);
            void saveScores() const;
            void getSavedScores();
        public:
            std::list<std::string> getGameLibs() const;
            std::list<std::string> getDisplayLibs() const;
            std::string &getGameInUse();
            std::string &getDisplayInUse();
            std::string getUsername() const;
            void setGameLibs(std::list<std::string> games);
            void setDisplayLibs(std::list<std::string> displays);
            void setGameInUse(std::string game);
            void setDisplayInUse(std::string display);
            void setUsername(std::string username);
        public:
            Menu &operator=(const Menu &obj);
        private:
            std::list<std::string> _games;
            std::list<std::string> _libs;
            std::string _libInUse;
            std::string _gameInUse = "";
            std::string _username = "";
            std::map<std::string, std::tuple<std::string, int>> _bestScore;
    };
}
