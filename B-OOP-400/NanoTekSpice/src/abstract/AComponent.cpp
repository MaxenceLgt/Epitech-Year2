/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** AComponent
*/

#include <iostream>
#include "Circuit.hpp"
#include "AComponent.hpp"

AComponent::AComponent()
{
    this->_actualState = nts::Tristate::Undefined;
    this->_tick = 0;
}

AComponent::~AComponent()
{
}

nts::Tristate AComponent::compute(std::size_t tick)
{
    (void)tick;
    throw AComponent::ComponentError("Trying to compute something that can't be computed.");
}

void AComponent::simulate(std::size_t tick)
{
    (void)tick;
}

void AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin, bool isPassed)
{
    nts::IComponent *component1 = nullptr;
    std::size_t pin2 = otherPin;

    if (dynamic_cast<CircuitComponent *>(this)) {
        component1 = dynamic_cast<CircuitComponent *>(this)->getAtPin(pin);
        if (component1 != nullptr) {
            return component1->setLink(0, other, otherPin, 0);
        }
        return;
    }
    if (dynamic_cast<CircuitComponent *>(&other)) {
        component1 = dynamic_cast<CircuitComponent *>(&other)->getAtPin(otherPin);
        pin2 = 0;
    } else
        component1 = &other;
    auto pair = this->_links.find(pin);
    if (pair != this->_links.end() && pair->second.back() == component1 && isPassed == 1)
        return;
    this->_links[pin].push_back(component1);
    if (component1 == nullptr)
        return;
    component1->setLink(pin2, *this, pin, 1);
}

AComponent &AComponent::operator=(const nts::Tristate &state)
{
    (void)state;
    throw AComponent::ComponentError("Impossible to modify state of non clock/input component.");
}
