/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** IDisplay
*/

#pragma once

    #include <iostream>
    #include <memory>
    #include "Event.hpp"
    #include "Object.hpp"

/**
 * @file IDisplay.hpp
 * @brief IDisplay class for the Arcade project
 **/
namespace Arcade {
    /**
     * @class IDisplay
     * @brief A class to represent a display in the Arcade project.
     *
     * This class contains methods to get the input, draw an object, clear the window, update the window, and play the turn.
    */
    class IDisplay {
        public:
            /**
            * @brief Destroy the IDisplay object
            *
            */
            virtual ~IDisplay() = default;

        public:
            /**
            * @brief Get the last input get by the graphic library
            *
            * @return Input
            */
            virtual Event getInput() = 0;

            /**
            * @brief Draw the object
            *
            * @param object
            */
            virtual void draw(std::shared_ptr<Object> object) = 0;

            /**
            * @brief Clear the window
            *
            */
            virtual void clearWindow() = 0;

            /**
            * @brief Update the window
            *
            */
            virtual void updateWindow() = 0;

            /**
            * @brief Play the next turn of game
            *
            * @return int number of turn to play
            */
            virtual int playTurn() = 0;

        private:
            /**
            * @brief Draw a rectangle
            *
            * @param object
            */
            virtual void drawRectangle(const std::shared_ptr<Object> object) = 0;

            /**
            * @brief Draw a circle
            *
            * @param object
            */
            virtual void drawCircle(const std::shared_ptr<Object> object) = 0;

            /**
            * @brief Draw a text
            *
            * @param object
            */
            virtual void drawText(const std::shared_ptr<Object> object) = 0;
    };
}
