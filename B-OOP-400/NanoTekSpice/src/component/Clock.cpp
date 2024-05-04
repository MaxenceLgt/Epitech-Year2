/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** ClockComponent
*/

#include "Clock.hpp"

ClockComponent::ClockComponent() : AComponent()
{
    this->_actualState = nts::Tristate::Undefined;
    this->_futurState = nts::Tristate::Undefined;
}

ClockComponent::ClockComponent(const ClockComponent &obj) : AComponent()
{
    this->_links = obj._links;
    this->_actualState = obj._actualState;
    this->_futurState = obj._futurState;
    this->_tick = obj._tick;
}

ClockComponent::~ClockComponent()
{
}

nts::Tristate ClockComponent::compute(std::size_t tick)
{
    this->_tick = tick;
    return this->_actualState;
}

void ClockComponent::simulate(std::size_t tick)
{
    this->_actualState = this->_futurState;

    (void)tick;
    if (this->_futurState == nts::Tristate::True)
        this->_futurState = nts::Tristate::False;
    else if (this->_futurState == nts::Tristate::False)
        this->_futurState = nts::Tristate::True;
}

ClockComponent &ClockComponent::operator=(const nts::Tristate &state)
{
    this->_futurState = state;
    return *this;
}

ClockComponent &ClockComponent::operator=(const ClockComponent &obj)
{
    if (this == &obj)
        return *this;
    this->_actualState = obj._actualState;
    this->_futurState = obj._futurState;
    this->_links = obj._links;
    this->_tick = obj._tick;
    return *this;
}