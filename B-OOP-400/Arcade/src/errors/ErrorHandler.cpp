/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** ErrorHandler
*/

#include "ErrorHandler.hpp"

Arcade::ErrorHandler::ErrorHandler()
{
}

Arcade::ErrorHandler::ErrorHandler(const ErrorHandler &obj)
{
    (void)obj;
}

Arcade::ErrorHandler::~ErrorHandler()
{
}

void Arcade::ErrorHandler::displayUsage() const
{
    std::string usage = "Arcade Usage:\n\n  ./arcade [lib]\n\n[lib]: \
The graphical lib use to run the program.";

    throw ErrorHandler::Error(usage);
}

void Arcade::ErrorHandler::checkArgumentsNumber(const int ac) const
{
    try {
        if (ac != 2)
            this->displayUsage();
    } catch (std::exception &e) {
        throw;
    }
}

void Arcade::ErrorHandler::checkLibValidity(const char *pathToLib) const
{
    LibHandler libChecker;
    std::string stringPath = pathToLib;

    try {
        void *handler = libChecker.openLib(stringPath, true);
        if (!libChecker.isDisplayLib(handler))
            throw ErrorHandler::Error("ErrorHandler : This lib " + stringPath + " does not correspond \
            project architecture");
    } catch (std::exception &e) {
        throw;
    }
}

Arcade::ErrorHandler &Arcade::ErrorHandler::operator=(const ErrorHandler &obj)
{
    if (&obj == this)
        return *this;
    return *this;
}
