/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** ClockComponent
*/

#pragma once

#include "AComponent.hpp"

class ClockComponent : public AComponent {
    public: //Ctor Dtor
        ClockComponent();
        ClockComponent(const ClockComponent &obj);
        ~ClockComponent();
    public: // Member function override
        nts::Tristate compute(std::size_t tick) override;
        void simulate(std::size_t tick) override;
    public: // operator overload
        ClockComponent &operator=(const nts::Tristate &state) override;
        ClockComponent &operator=(const ClockComponent &obj);
    private: // Class variables
        nts::Tristate _futurState;
};
