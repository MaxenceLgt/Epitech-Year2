/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** IComponent
*/

#pragma once

#include <string>
#include <memory>

namespace nts {

    enum Tristate {
        Undefined = (- true),
        True = true,
        False = false
    };

    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual void simulate(std::size_t tick) = 0;
            virtual nts::Tristate compute(std::size_t tick) = 0;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std ::size_t otherPin, bool isPassed) = 0;
        public:
            virtual nts::IComponent &operator=(const nts::Tristate &state) = 0;
    };
}
