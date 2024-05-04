/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** True
*/

#pragma once

#include "AComponent.hpp"

class TrueComponent : public AComponent {
    public: // CTOR DTOR
        TrueComponent();
        TrueComponent(const TrueComponent &obj);
        ~TrueComponent();
    public: // Member function override
        nts::Tristate compute(std::size_t tick) override;
    public: // operator overload
        TrueComponent &operator=(const nts::Tristate &state) override;
        TrueComponent &operator=(const TrueComponent &obj);
};
