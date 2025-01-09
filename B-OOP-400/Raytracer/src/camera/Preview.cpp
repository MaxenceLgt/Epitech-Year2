/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** preview
*/

#include "Preview.hpp"

Preview::Preview(int image_width, int image_height)
{
    this->image_width = image_width;
    this->image_height = image_height;
    image.create(image_width, image_height, sf::Color::Black);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

Preview::~Preview()
{
    this->window.close();
}

void Preview::init()
{
    window.create(sf::VideoMode(image_width, image_height), "Raytracer");
}

bool Preview::display()
{
    init();
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            //enter = return true
            //echap == return false
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    window.close();
                    return true;
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return false;
                }
            }
        }
        texture.update(image);
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return true;
}
