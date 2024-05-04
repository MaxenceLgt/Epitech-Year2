/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** CircuitComponent
*/

#pragma once

#include "AComponent.hpp"
#include "parsing.hpp"
#include <unordered_map>
#include <string>
#include <list>

class CircuitComponent : public AComponent {
    public: // Ctor Dtor
        CircuitComponent();
        CircuitComponent(const CircuitComponent &obj);
        CircuitComponent(const std::string &component);
        ~CircuitComponent();
    public: // Member functions
        Parsing getParser();
        std::size_t getTick();
        std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> getMapComponent();
        std::unordered_map<std::string, std::size_t> getMapLinks();
        std::shared_ptr<nts::IComponent> findComponent(const std::string name);
        nts::IComponent *getAtPin(std::size_t pin);
        void addComponent(std::shared_ptr<nts::IComponent> component, std::string name);
        void fillCircuitComponent(std::string filename);
        void display();
    public: // Member function override
        void simulate(std::size_t tick) override;
    public: // Operator overload
        CircuitComponent &operator=(const nts::Tristate &state) override;
        CircuitComponent &operator=(const CircuitComponent &obj);
    private: // Class variables
        std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> _mapComponent;
        std::unordered_map<std::string, std::size_t> _linkIndex;
        Parsing parser;
};
