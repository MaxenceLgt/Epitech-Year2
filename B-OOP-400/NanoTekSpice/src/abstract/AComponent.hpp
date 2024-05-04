/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** AComponent
*/

#pragma once

#include "IComponent.hpp"
#include <vector>
#include <unordered_map>

class AComponent : public nts::IComponent {
    protected: // Ctor Dtor
        AComponent();
        ~AComponent();
    public: // Member functions override
        virtual nts::Tristate compute(std::size_t tick) override;
        void simulate(std::size_t tick) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin, bool isPassed) override;
    public: // Operator overload
        AComponent &operator=(const nts::Tristate &state) override;
    public: // Error Class
        class ComponentError : public std::exception {
            public:
                ComponentError(std::string msg) : _msg(msg) {};
                ~ComponentError() {};
            private:
                const char *what() const noexcept override {return _msg.c_str();};
            private:
                std::string _msg;
        };
    protected: // Class variables
        std::unordered_map<std::size_t, std::vector<nts::IComponent *>> _links;
        nts::Tristate _actualState;
        std::size_t _tick;
};
