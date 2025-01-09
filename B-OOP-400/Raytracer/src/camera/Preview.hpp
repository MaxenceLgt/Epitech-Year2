/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** preview
*/

#pragma once

#include "Utils.hpp"
#include <SFML/Graphics.hpp>

class Preview {
    public:
        Preview(int image_width, int image_height);
        ~Preview();
        void init();
        bool display();
        double image_width;
        double image_height;
        sf::RenderWindow window;
        sf::Image image;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Event event;
        sf::Color sfml_color;
};
