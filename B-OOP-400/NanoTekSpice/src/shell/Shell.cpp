/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu-22.04]
** File description:
** Shell.cpp
*/

#include "Shell.hpp"


Shell::Shell()
{
}

Shell::Shell(const Shell &obj)
{
    this->_mainCircuit = obj._mainCircuit;
}

Shell::~Shell()
{
}

void Shell::run(const std::string file)
{
    std::signal(SIGINT, [](int /*signum*/) { _flag.clear();});
    this->_mainCircuit.fillCircuitComponent(file);
    this->computeComponents();
    while (true) {
        std::regex pattern(R"((\w+)=(\w+)?\n?$)");

        std::smatch matches;
        std::string commande;

        std::cout << "> ";
        std::getline(std::cin, commande);

        if (std::cin.eof()) {
            break;
        }
        if (commande == "exit")
            break;
        if (commande == "display") {
            this->_mainCircuit.display();
            continue;
        }
        if (commande == "loop") {
            while (_flag.test_and_set()) {
                this->_mainCircuit.simulate(this->_mainCircuit.getTick() + 1);
                this->_mainCircuit.display();
            }
            continue;
        }
        if (commande == "simulate") {
            this->_mainCircuit.simulate(this->_mainCircuit.getTick() + 1);
            continue;
        }
        if (std::regex_search(commande, matches, pattern)) {
            if (this->_mainCircuit.findComponent(matches[1]) == nullptr) {
                continue;
            }
            if (matches[2] != "0" && matches[2] != "1" && matches[2] != "U") {
                continue;
            }
            std::shared_ptr<nts::IComponent> component = this->_mainCircuit.findComponent(matches[1]);
            if (matches[2] == "0") {
                *component = nts::Tristate::False;
            }
            if (matches[2] == "1") {
                *component = nts::Tristate::True;
            }
            if (matches[2] == "U") {
                *component = nts::Tristate::Undefined;
            }
        }
    }
}

void Shell::computeComponents()
{
    nts::Tristate computeValue = nts::Tristate::Undefined;

    std::list<std::string> inputs = this->_mainCircuit.getParser().getInputs();
    for (auto elm : inputs) {
        std::shared_ptr<nts::IComponent> component = this->_mainCircuit.findComponent(elm);
        if (component != nullptr)
            computeValue = component->compute(this->_mainCircuit.getTick() + 1);
        if (computeValue == -1) {
            computeValue = nts::Tristate::Undefined;
            continue;
        }
        computeValue = nts::Tristate::Undefined;
    }
    std::list<std::string> outputs = this->_mainCircuit.getParser().getOutputs();
    for (auto elm : outputs) {
        std::shared_ptr<nts::IComponent> component = this->_mainCircuit.findComponent(elm);
        if (component != nullptr)
            computeValue = component->compute(this->_mainCircuit.getTick() + 1);
        if (computeValue == -1) {
            computeValue = nts::Tristate::Undefined;
            continue;
        }
        computeValue = nts::Tristate::Undefined;
    }
    return;
}

Shell &Shell::operator=(const Shell &obj)
{
    if (this == &obj)
        return *this;
    this->_mainCircuit = obj._mainCircuit;
    return *this;
}
