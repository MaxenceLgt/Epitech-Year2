/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** NandComponent
*/

#pragma once

#include "AComponent.hpp"

class NandComponent : public AComponent {
    public: // Ctor Dtor
        NandComponent();
        NandComponent(const NandComponent &obj);
        ~NandComponent();
    public: // Member Function override
        nts::Tristate compute(std::size_t tick) override;
    public: // Operator overload
        NandComponent &operator=(const nts::Tristate &state) override;
        NandComponent &operator=(const NandComponent &obj);
};
