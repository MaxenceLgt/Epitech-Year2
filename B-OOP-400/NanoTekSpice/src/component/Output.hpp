/*
** EPITECH PROJECT, 2024
** OutputComponent
** File description:
** OutputComponent
*/

#pragma once

#include "AComponent.hpp"

class OutputComponent : public AComponent {
    public: // Ctor Dtor
        OutputComponent();
        OutputComponent(const OutputComponent &obj);
        ~OutputComponent();
    public: // Member function override
        nts::Tristate compute(std::size_t tick) override;
    public: // Operator overload
        OutputComponent &operator=(const nts::Tristate &state) override;
        OutputComponent &operator=(const OutputComponent &obj);
};
