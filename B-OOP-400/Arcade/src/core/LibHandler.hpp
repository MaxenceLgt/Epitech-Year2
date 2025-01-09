/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** LibHandler
*/

#pragma once

    #include <string>
    #include <list>
    #include <dlfcn.h>

namespace Arcade { 
    class LibHandler {
        public:
            LibHandler();
            LibHandler(const LibHandler &obj);
            ~LibHandler();
        public:
            void *openLib(const std::string libPath, const bool throwOnError = false) const;
            void closeLib(void *libOpened) const;
            bool isDisplayLib(void *libOpened, bool closeLib = true) const;
            bool isGameLib(void *libOpened, bool closeLib = true) const;
            bool libIsChecked(const std::list<std::string> libList, const std::string lib) const;
            template<typename T>
            T *libLoader(const std::string pathToLib) const {
                void *handler = this->openLib(pathToLib);
                void *(*fptr)();
                if (this->isDisplayLib(handler, false))
                    fptr = (void*(*)())dlsym(handler, "entryPointDisplay");
                else
                    fptr = (void*(*)())dlsym(handler, "entryPointGame");
                dlclose(handler);
                return ((T *)fptr());
            };
        public:
            class LibHandlerError : public std::exception {
                public:
                    LibHandlerError(std::string msg) : _msg(msg) {};
                    ~LibHandlerError() {};
                private:
                    const char *what() const noexcept override {return _msg.c_str();};
                private:
                    std::string _msg;
            };
        public:
            LibHandler &operator=(const LibHandler &obj);
    };
}
