/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu-22.04]
** File description:
** Shell.hpp
*/

#pragma once

    
    #include <csignal>
    #include <atomic>
    #include <iostream>
    #include "Circuit.hpp"

class Shell {
    public: // Ctor Dtor
        Shell();
        Shell(const Shell &obj);
        ~Shell();
    public: // Member function
        void run(const std::string file);
        void computeComponents();
    public: // Operator overload
        Shell &operator=(const Shell &obj);
    private: // Class variables
        CircuitComponent _mainCircuit;
};

static std::atomic_flag _flag = ATOMIC_FLAG_INIT;