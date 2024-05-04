/*
** EPITECH PROJECT, 2024
** ComponentFactory
** File description:
** ComponentFactory
*/

#pragma once

    #include <memory>
    #include <string>
    #include <unordered_map>
    #include <exception>
    #include <functional>
    #include "True.hpp"
    #include "False.hpp"
    #include "Input.hpp"
    #include "Output.hpp"
    #include "Clock.hpp"
    #include "Nand.hpp"

class ComponentFactory {
    public: // Ctor Dtor
        ComponentFactory();
        ComponentFactory(const ComponentFactory &obj);
        ~ComponentFactory();
    public: // Member functions
        bool isMappedComponent(const std::string &type);
        std::shared_ptr<nts::IComponent> createComponent(const std::string &type);
        std::unordered_map<std::string, std::function<std::shared_ptr<nts::IComponent>()>> getMap() const;
    public:
        ComponentFactory &operator=(const ComponentFactory &obj);
    public: // Nested Error Class
        class FactoryError : public std::exception {
            public:
                FactoryError(std::string msg) : _msg(msg) {};
                ~FactoryError() {};
            private:
                const char *what() const noexcept override {return _msg.c_str();};
            private:
                std::string _msg;
        };
    private: // Class variables
        std::unordered_map<std::string, std::function<std::shared_ptr<nts::IComponent>()>> _creationMap;
};
