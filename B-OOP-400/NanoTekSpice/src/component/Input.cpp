/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** IO
*/

#include <iostream>
#include "Input.hpp"

InputComponent::InputComponent() : AComponent()
{
    this->_actualState = nts::Tristate::Undefined;
    this->_futurState = nts::Tristate::Undefined;
}

InputComponent::InputComponent(const InputComponent &obj) : AComponent()
{
    this->_links = obj._links;
    this->_tick = obj._tick;
    this->_actualState = obj._actualState;
    this->_futurState = obj._futurState;
}

InputComponent::~InputComponent()
{
}

nts::Tristate InputComponent::compute(std::size_t tick)
{
    if (this->_tick == tick)
        return this->_actualState;
    this->_tick = tick;
    if (this->_links.size() <= 1)
        return this->_actualState; //Dans le cas ou un link next ou aucun link est set
    auto pair = this->_links.find(0);
    if (pair == this->_links.end())
        return this->_actualState;
    if (pair->second.at(0)) // Si j'ai un previous je change mon state;
        this->_actualState = pair->second.at(0)->compute(tick);
    return this->_actualState;
}

void InputComponent::simulate(std::size_t tick)
{
    (void)tick;
    if (_links.size() > 1)
        return;
    this->_actualState = this->_futurState;
}

InputComponent &InputComponent::operator=(const nts::Tristate &state)
{
    if (this->_links.size() <= 1)
        this->_futurState = state;
    return *this;
}

InputComponent &InputComponent::operator=(const InputComponent &obj)
{
    if (this == &obj)
        return *this;
    this->_actualState = obj._actualState;
    this->_futurState = obj._futurState;
    this->_links = obj._links;
    this->_tick = obj._tick;
    return *this;
}