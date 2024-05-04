/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** TrueComponent
*/

#include "True.hpp"

TrueComponent::TrueComponent() : AComponent()
{
    this->_actualState = nts::Tristate::True;
}

TrueComponent::TrueComponent(const TrueComponent &obj) : AComponent()
{
    this->_links = obj._links;
    this->_actualState = obj._actualState;
    this->_tick = obj._tick;
}

TrueComponent::~TrueComponent()
{
}

nts::Tristate TrueComponent::compute (std::size_t tick)
{
    this->_tick = tick;
    return this->_actualState;
}

TrueComponent &TrueComponent::operator=(const nts::Tristate &state)
{
    (void)state;
    throw AComponent::ComponentError("TrueComponent : Trying to change state of TrueComponent component");
}

TrueComponent &TrueComponent::operator=(const TrueComponent &obj)
{
    if (this == &obj)
        return *this;
    this->_actualState = obj._actualState;
    this->_links = obj._links;
    this->_tick = obj._tick;
    return *this;
}