/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** FalseComponent
*/

#include "False.hpp"

FalseComponent::FalseComponent() : AComponent()
{
    this->_actualState = nts::Tristate::False;
}

FalseComponent::FalseComponent(const FalseComponent &obj) : AComponent()
{
    this->_links = obj._links;
    this->_actualState = obj._actualState;
    this->_tick = obj._tick;
}

FalseComponent::~FalseComponent()
{
}

nts::Tristate FalseComponent::compute(std::size_t tick)
{
    this->_tick = tick;
    return this->_actualState;
}

FalseComponent &FalseComponent::operator=(const nts::Tristate &state)
{
    (void)state;
    throw AComponent::ComponentError("FalseComponent : Trying to change state of FalseComponent component");
}

FalseComponent &FalseComponent::operator=(const FalseComponent &obj)
{
    if (this == &obj)
        return *this;
    this->_actualState = obj._actualState;
    this->_links = obj._links;
    this->_tick = obj._tick;
    return *this;
}