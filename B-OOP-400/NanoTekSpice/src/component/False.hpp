/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** FalseComponent
*/

#pragma once

#include "AComponent.hpp"

class FalseComponent : public AComponent {
    public: //Ctor Dtor
        FalseComponent();
        FalseComponent(const FalseComponent &obj);
        ~FalseComponent();
    public: // Member function override
        nts::Tristate compute(std::size_t tick) override;
    public: // Operator overload
        FalseComponent &operator=(const nts::Tristate &state) override;
        FalseComponent &operator=(const FalseComponent &obj);
};
