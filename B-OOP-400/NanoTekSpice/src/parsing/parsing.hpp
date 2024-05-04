/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** parsing
*/

#pragma once

    #include <string>
    #include <fstream>
    #include <vector>
    #include <sstream>
    #include <unordered_map>
    #include <exception>
    #include <functional>
    #include <memory>
    #include "IComponent.hpp"
    #include "ComponentFactory.hpp"
    #include <regex>
    #include <list>

class Parsing
{
    public: // Ctor Dtor
        Parsing();
        Parsing(const Parsing &parsing);
        ~Parsing();
    public: // Member functions
        void parsingFile(std::string fileName, std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> &_map, std::unordered_map<std::string, std::size_t> &_linkIndex);
        void parsingChipset(std::string ligne, std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> &_map,int nbr, std::unordered_map<std::string, std::size_t> &_linkIndex);
        void parsingLink(std::string ligne, std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> &_map);
        bool mapContain(std::string componentName, std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> &_map);
        std::list<std::string> getInputs();
        std::list<std::string> getOutputs();
    public:
        Parsing &operator=(const Parsing &object);
    public: // Nested Error Class
        class ParsingError : public std::exception {
            public:
                ParsingError(std::string msg) : _msg(msg) {};
                ~ParsingError() {};
            private:
                const char *what() const noexcept override {return _msg.c_str();};
            private:
                std::string _msg;
        };
    protected: // Class variables
        ComponentFactory _factory;
        std::list<std::string> inputs;
        std::list<std::string> outputs;
};
