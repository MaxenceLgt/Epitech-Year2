/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** IGame
*/

#pragma once

    #include <iostream>
    #include <vector>
    #include <memory>
    #include "Event.hpp"
    #include "Object.hpp"

/**
 * @file IGame.hpp
 * @brief IGame class for the Arcade project
 **/
namespace Arcade {
    /**
     * @class IGame
     * @brief A class to represent a game in the Arcade project.
     *
     * This class contains methods to play a turn, start the game, and get the score.
     */
    class IGame {
        public:
            /**
             * @brief Destroy the IGame object
             *
             */
            virtual ~IGame() = default;

        public:
            /**
             * @brief Play a turn
             *
             * @param event The event to play the turn with.
             */
            virtual std::vector<std::shared_ptr<Object>> Turn(Event event) = 0;

            /**
             * @brief init the game
             *
             */
            virtual void init() = 0;

            /**
             * @brief Get the score
             *
             * @return int The score of the game.
             */
            virtual int getScore() = 0;
    };
}
