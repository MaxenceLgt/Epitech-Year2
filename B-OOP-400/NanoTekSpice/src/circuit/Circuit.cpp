/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** CircuitComponent
*/

#include <iostream>
#include <csignal>
#include <atomic>
#include "Circuit.hpp"


CircuitComponent::CircuitComponent() : AComponent()
{
}

CircuitComponent::CircuitComponent(const CircuitComponent &obj) : AComponent()
{
    this->_actualState = obj._actualState;
    this->parser = obj.parser;
    this->_linkIndex = obj._linkIndex;
    this->_links = obj._links;
    this->_mapComponent = obj._mapComponent;
    this->_tick = obj._tick;
}

CircuitComponent::CircuitComponent(const std::string &component)
{
    parser.parsingFile("src/config/" + component + "_config.nts", this->_mapComponent, this->_linkIndex);
}

CircuitComponent::~CircuitComponent()
{
}

std::shared_ptr<nts::IComponent> CircuitComponent::findComponent(const std::string name)
{
    auto key = this->_mapComponent.find(name);
    if (key == this->_mapComponent.end()) {
        return nullptr;
    }
    return key->second;
}

void CircuitComponent::addComponent(std::shared_ptr<nts::IComponent> component, std::string name)
{
    if (component == nullptr)
        throw AComponent::ComponentError("CircuitComponent: Trying to add nullptr to map!");
    this->_mapComponent[name] = component;
}

void CircuitComponent::simulate(std::size_t tick)
{
    this->_tick = tick;
    for (auto pair : this->_mapComponent)
        if (pair.second)
            pair.second->simulate(tick);
}

nts::IComponent *CircuitComponent::getAtPin(std::size_t pin)
{
    std::string componentName;

    for (auto pair : this->_linkIndex) {
        if (pair.second == pin)
            componentName = pair.first;
    }
    if (componentName.empty())
        return nullptr;
    auto pair = this->_mapComponent.find(componentName);
    if (pair == this->_mapComponent.end())
        return nullptr;
    return pair->second.get();
}

void CircuitComponent::display()
{
    nts::Tristate computeValue = nts::Tristate::Undefined;

    std::cout << "tick: " << this->_tick << std::endl;
    std::cout << "input(s):" << std::endl;
    std::list<std::string> inputs = this->parser.getInputs();
    inputs.sort();
    for (auto elm : inputs) {
        std::shared_ptr<nts::IComponent> component = findComponent(elm);
        if (component != nullptr) {
            computeValue = component->compute(this->_tick + 1);
        }
        if (computeValue == -1) {
            std::cout << "  " << elm << ": " << "U" << std::endl;
            computeValue = nts::Tristate::Undefined;
            continue;
        }
        std::cout << "  " << elm << ": " << computeValue << std::endl;
        computeValue = nts::Tristate::Undefined;
    }
    std::cout << "output(s):" << std::endl;
    std::list<std::string> outputs = this->parser.getOutputs();
    outputs.sort();
    for (auto elm : outputs) {
        std::shared_ptr<nts::IComponent> component = findComponent(elm);
        if (component != nullptr) {
            computeValue = component->compute(this->_tick + 1);
        }
        if (computeValue == -1) {
            std::cout << "  " << elm << ": " << "U" << std::endl;
            computeValue = nts::Tristate::Undefined;
            continue;
        }
        std::cout << "  " << elm << ": " << computeValue << std::endl;
        computeValue = nts::Tristate::Undefined;
    }
    return;
}

Parsing CircuitComponent::getParser()
{
    return this->parser;
}

std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> CircuitComponent::getMapComponent()
{
    return this->_mapComponent;
}

std::unordered_map<std::string, std::size_t> CircuitComponent::getMapLinks()
{
    return this->_linkIndex;
}

void CircuitComponent::fillCircuitComponent(std::string filename)
{
    this->parser.parsingFile(filename, _mapComponent, _linkIndex);
    return;
}

std::size_t CircuitComponent::getTick()
{
    return _tick;
}

CircuitComponent &CircuitComponent::operator=(const nts::Tristate &state)
{
    (void)state;
    throw AComponent::ComponentError("CircuitComponent : Trying to change state of CircuitComponent component");
}

CircuitComponent &CircuitComponent::operator=(const CircuitComponent &obj)
{
    if (this == &obj)
        return *this;
    this->_actualState = obj._actualState;
    this->parser = obj.parser;
    this->_linkIndex = obj._linkIndex;
    this->_links = obj._links;
    this->_mapComponent = obj._mapComponent;
    this->_tick = obj._tick;
    return *this;
}