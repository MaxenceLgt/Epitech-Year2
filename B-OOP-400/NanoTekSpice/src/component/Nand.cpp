/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** NandComponent
*/

#include <iostream>
#include "Nand.hpp"

NandComponent::NandComponent() : AComponent()
{
    this->_actualState = nts::Tristate::Undefined;
}

NandComponent::NandComponent(const NandComponent &obj) : AComponent()
{
    this->_links = obj._links;
    this->_actualState = obj._actualState;
    this->_tick = obj._tick;
}

NandComponent::~NandComponent()
{
}

nts::Tristate NandComponent::compute(std::size_t tick)
{
    nts::Tristate a = nts::Tristate::Undefined;
    nts::Tristate b = nts::Tristate::Undefined;

    if (this->_tick == tick)
        return this->_actualState;
    this->_tick = tick;
    auto pair1 = this->_links.find(1);
    auto pair2 = this->_links.find(2);

    if (pair2 != this->_links.end()) {
        if (pair2->second.at(0)) {
            b = pair2->second.at(0)->compute(tick);
        }
    }
    if (pair1 != this->_links.end()) {
        if (pair1->second.at(0)) {
            a = pair1->second.at(0)->compute(tick);
        }
    }
    if (a == nts::Tristate::Undefined && b == nts::Tristate::Undefined)
        this->_actualState = nts::Tristate::Undefined;
    if ((a == nts::Tristate::True || b == nts::Tristate::True) && (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined))
        this->_actualState = nts::Tristate::Undefined;
    if (a == nts::Tristate::False || b == nts::Tristate::False)
        this->_actualState = nts::Tristate::True;
    if (a == nts::Tristate::True && b == nts::Tristate::True)
        this->_actualState = nts::Tristate::False;
    return this->_actualState;
}

NandComponent &NandComponent::operator=(const nts::Tristate &state)
{
    (void)state;
    throw AComponent::ComponentError("True : Trying to change state of true component");
}

NandComponent &NandComponent::operator=(const NandComponent &obj)
{
    if (this == &obj)
        return *this;
    this->_actualState = obj._actualState;
    this->_links = obj._links;
    this->_tick = obj._tick;
    return *this;
}