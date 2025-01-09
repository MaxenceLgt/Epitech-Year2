/*
** EPITECH PROJECT, 2024
** bsarcarde
** File description:
** CLibEncapsulation
*/

#pragma once

#include <dlfcn.h>
#include <libconfig.h++>
#include <iostream>

class CLibEncapsulation {
    public:
        CLibEncapsulation();
        CLibEncapsulation(std::string &libPath);
        ~CLibEncapsulation();
        void openLib(std::string const libPath);
        void closeLib();
        void *getLib();
        void *getFunction(std::string const &functionName);
        /**
         * @brief Get an element from the library.
         *
         * @tparam T The type of the element to get.
         * @param elementName The name of the element to get.
         * @return T The element.
         */
        template<class T>
        T getElement(const libconfig::Setting &settings) {
            if (!this->isLibOpen) {
                this->setError("Library is not open");
                return nullptr;
            }
            T (*element)(const libconfig::Setting &) = (T (*)(const libconfig::Setting &) ) getFunction("entryPoint");
            if (!element) {
                this->setError(dlerror());
                return nullptr;
            }
            T elementPtr = (T)element(settings);
            if (!elementPtr) {
                this->setError(dlerror());
                return nullptr;
            }
            return elementPtr;
        }
        std::string getError();

    public:
        bool isLibOpen = false;
        bool failed = false;

    private:
        void *lib = nullptr;
        std::string libPath;
        void setError(std::string const &error);
        std::string _error;

public:
    class LibException : public std::exception {
        public:
            LibException(std::string const &message) throw() : _message(message) {}
            const char *what() const throw() { return _message.c_str(); }
            ~LibException() throw() {}
        private:
            std::string _message;
    };
};
