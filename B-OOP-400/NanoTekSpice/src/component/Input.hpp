/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** componentIO
*/

#pragma once

#include "AComponent.hpp"

class InputComponent : public AComponent {
    public: // Ctor Dtor
        InputComponent();
        InputComponent(const InputComponent &obj);
        ~InputComponent();
    public: // Member function override
        nts::Tristate compute(std::size_t pin) override;
        void simulate(std::size_t tick) override;
    public: // Operator overload
        InputComponent &operator=(const nts::Tristate &state) override;
        InputComponent &operator=(const InputComponent &obj);
    private: // Class variables
        nts::Tristate _futurState;
};
