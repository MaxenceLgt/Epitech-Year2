/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** ErrorHandler
*/

#pragma once

    #include <exception>
    #include <string>
    #include "LibHandler.hpp"

namespace Arcade {
    class ErrorHandler {
        public:
            ErrorHandler();
            ErrorHandler(const ErrorHandler &obj);
            ~ErrorHandler();
        public:
            void displayUsage() const;
            void checkArgumentsNumber(const int ac) const;
            void checkLibValidity(const char *pathToLib) const;
        public:
            ErrorHandler &operator=(const ErrorHandler &obj);
        public:
            class Error : public std::exception {
                public:
                    Error(std::string msg) : _msg(msg) {};
                    ~Error() {};
                private:
                    const char *what() const noexcept override {return _msg.c_str();};
                private:
                    std::string _msg;
            };
    };
}