/*
** EPITECH PROJECT, 2023
** Arcade [WSL: Ubuntu-22.04]
** File description:
** Core.hpp
*/

#pragma once

    #include <memory>
    #include <list>
    #include <exception>
    #include <dlfcn.h>
    #include "IGame.hpp"
    #include "IDisplay.hpp"
    #include "LibHandler.hpp"
    #include "Menu.hpp"

namespace Arcade {
    class Core {
        public:
            Core(std::string display);
            Core(const Core &obj);
            ~Core();
        public:
            void mainLoop();
            void refreshLib() const;
            void manageInput(Event &userInput, std::vector<std::shared_ptr<Object>> objects);
        public:
            Arcade::Core &operator=(const Core &obj);
        public:
            class CoreError : public std::exception {
                public:
                    CoreError(std::string msg) : _msg(msg) {};
                    ~CoreError() {};
                private:
                    const char *what() const noexcept override {return _msg.c_str();};
                private:
                    std::string _msg;
            };
        public:
            template<typename T>
            void switchNextLib(std::list<std::string> listToCheck, std::string &libInUse, std::unique_ptr<T> &objToChange) const
            {
                LibHandler libManager;

                if (listToCheck.empty())
                    return;
                for (auto it = listToCheck.begin(); it != listToCheck.end(); it++) {
                    if (*it == libInUse) {
                        it++;
                        if (it != listToCheck.end()) {
                            libInUse = *it;
                            objToChange = nullptr;
                            objToChange = std::unique_ptr<T>(libManager.libLoader<T>(libInUse));
                            return;
                        }
                        break;
                    }
                }
                libInUse = *listToCheck.begin();
                objToChange = nullptr;
                objToChange = std::unique_ptr<T>(libManager.libLoader<T>(libInUse));
            };

            template<typename T>
            void switchPrevLib(std::list<std::string> listToCheck, std::string &libInUse, std::unique_ptr<T> &objToChange) const
            {
                LibHandler libManager;

                if (listToCheck.empty())
                    return;
                for (auto it = listToCheck.begin(); it != listToCheck.end(); it++) {
                    if (*it == libInUse && it != listToCheck.begin()) {
                        it--;
                        libInUse = *it;
                        objToChange = nullptr;
                        objToChange = std::unique_ptr<T>(libManager.libLoader<T>(libInUse));
                        return;
                    }
                }
                libInUse = *(--listToCheck.end());
                objToChange = nullptr;
                objToChange = std::unique_ptr<T>(libManager.libLoader<T>(libInUse));
            };
        private:
            std::unique_ptr<Menu> _menu;
            std::unique_ptr<IGame> _game;
            std::unique_ptr<IDisplay> _display;
            bool _isPlaying = true;
            bool _isDisplayMenu = true;
    };
}
