/*
** EPITECH PROJECT, 2024
** OutputComponent
** File description:
** OutputComponent
*/

#include <iostream>
#include "Output.hpp"

OutputComponent::OutputComponent() : AComponent()
{
    this->_actualState = nts::Tristate::Undefined;
}

OutputComponent::OutputComponent(const OutputComponent &obj) : AComponent()
{
    this->_links = obj._links;
    this->_actualState = obj._actualState;
    this->_tick = obj._tick;
}

OutputComponent::~OutputComponent()
{
}

nts::Tristate OutputComponent::compute(std::size_t tick)
{
    if (this->_tick == tick || _links.size() < 1)
        return this->_actualState;
    this->_tick = tick;
    auto pair = this->_links.find(1);
    if (pair != this->_links.end()) {
        std::vector<nts::IComponent *> linkedComponents = pair->second;
        if (!linkedComponents.empty() && linkedComponents.at(0) != nullptr) {
            this->_actualState = linkedComponents.at(0)->compute(tick);
            return this->_actualState;
        }
    }
    return this->_actualState;
}

OutputComponent &OutputComponent::operator=(const nts::Tristate &state)
{
    (void)state;
    throw AComponent::ComponentError("True : Trying to change state of true component");
}

OutputComponent &OutputComponent::operator=(const OutputComponent &obj)
{
    if (this == &obj)
        return *this;
    this->_actualState = obj._actualState;
    this->_links = obj._links;
    this->_tick = obj._tick;
    return *this;
}