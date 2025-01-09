/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** LibHandler
*/

#include "LibHandler.hpp"

Arcade::LibHandler::LibHandler()
{
}


Arcade::LibHandler::LibHandler(const Arcade::LibHandler &obj)
{
    (void)obj;
}

Arcade::LibHandler::~LibHandler()
{
}

void *Arcade::LibHandler::openLib(const std::string libPath, const bool throwOnError) const
{
    void *handle = dlopen(libPath.c_str(), RTLD_NOW | RTLD_NODELETE);

    if (handle == nullptr && throwOnError)
        throw LibHandler::LibHandlerError(dlerror());
    return handle;
}

void Arcade::LibHandler::closeLib(void *libOpened) const
{
    dlclose(libOpened);
}

bool Arcade::LibHandler::isDisplayLib(void *libOpened, bool closeLib) const
{
    void *(*fptr)();
    bool result = false;

    if (!libOpened)
        return result;
    fptr = (void*(*)())dlsym(libOpened, "entryPointDisplay");
    if (fptr != nullptr)
        result = true;
    if (closeLib)
        this->closeLib(libOpened);
    return result;
}

bool Arcade::LibHandler::isGameLib(void *libOpened, bool closeLib) const
{
    void *(*fptr)();
    bool result = false;

    if (!libOpened)
        return result;
    fptr = (void*(*)())dlsym(libOpened, "entryPointGame");
    if (fptr != nullptr)
        result = true;
    if (closeLib)
        this->closeLib(libOpened);
    return result;
}

bool Arcade::LibHandler::libIsChecked(const std::list<std::string> libList, const std::string lib) const
{
    for (const auto &libOfList : libList) {
        if (libOfList == lib)
            return true;
    }
    return false;
}

Arcade::LibHandler &Arcade::LibHandler::operator=(const Arcade::LibHandler &obj)
{
    (void)obj;
    return *this;
}
