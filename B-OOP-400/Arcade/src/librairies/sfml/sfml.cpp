/*
** EPITECH PROJECT, 2024
** Arcade [WSL: Ubuntu]
** File description:
** sfml
*/

#include "sfml.hpp"

namespace Arcade {

    void SFML::clearWindow()
    {
        _window.clear(sf::Color::Black);
    }

    void SFML::updateWindow()
    {
        _window.display();
    }

    Event SFML::getInput()
    {
        sf::Event event = {};

        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return (Event::ESCAPE);
            if (event.type != sf::Event::KeyPressed)
                continue;
            switch (event.key.code) {
                case sf::Keyboard::F1:
                    return (Event::PREV_LIB);
                case sf::Keyboard::F2:
                    return (Event::NEXT_LIB);
                case sf::Keyboard::F3:
                    return (Event::PREV_GAME);
                case sf::Keyboard::F4:
                    return (Event::NEXT_GAME);
                case sf::Keyboard::F5:
                    return (Event::GAME_RESTART);
                case sf::Keyboard::F6:
                    return (Event::MENU);
                case sf::Keyboard::Enter:
                    return (Event::ENTER);
                case sf::Keyboard::Space:
                    return (Event::SPACE);
                case sf::Keyboard::Up:
                    return (Event::GAME_UP);
                case sf::Keyboard::Down:
                    return (Event::GAME_DOWN);
                case sf::Keyboard::Left:
                    return (Event::GAME_LEFT);
                case sf::Keyboard::Right:
                    return (Event::GAME_RIGHT);
                case sf::Keyboard::Escape:
                    return (Event::ESCAPE);
                case sf::Keyboard::Backspace:
                    return (Event::BACKSPACE);
                case sf::Keyboard::A:
                    return (Event::IN_A);
                case sf::Keyboard::B:
                    return (Event::IN_B);
                case sf::Keyboard::C:
                    return (Event::IN_C);
                case sf::Keyboard::D:
                    return (Event::IN_D);
                case sf::Keyboard::E:
                    return (Event::IN_E);
                case sf::Keyboard::F:
                    return (Event::IN_F);
                case sf::Keyboard::G:
                    return (Event::IN_G);
                case sf::Keyboard::H:
                    return (Event::IN_H);
                case sf::Keyboard::I:
                    return (Event::IN_I);
                case sf::Keyboard::J:
                    return (Event::IN_J);
                case sf::Keyboard::K:
                    return (Event::IN_K);
                case sf::Keyboard::L:
                    return (Event::IN_L);
                case sf::Keyboard::M:
                    return (Event::IN_M);
                case sf::Keyboard::N:
                    return (Event::IN_N);
                case sf::Keyboard::O:
                    return (Event::IN_O);
                case sf::Keyboard::P:
                    return (Event::IN_P);
                case sf::Keyboard::Q:
                    return (Event::IN_Q);
                case sf::Keyboard::R:
                    return (Event::IN_R);
                case sf::Keyboard::S:
                    return (Event::IN_S);
                case sf::Keyboard::T:
                    return (Event::IN_T);
                case sf::Keyboard::U:
                    return (Event::IN_U);
                case sf::Keyboard::V:
                    return (Event::IN_V);
                case sf::Keyboard::W:
                    return (Event::IN_W);
                case sf::Keyboard::X:
                    return (Event::IN_X);
                case sf::Keyboard::Y:
                    return (Event::IN_Y);
                case sf::Keyboard::Z:
                    return (Event::IN_Z);
                default:
                    break;
            }
        }
        return NONE;
    }

    sf::Color SFML::defineColor(Arcade::Color color)
    {
        switch (color) {
            case Arcade::Color::BLACK:
                return sf::Color::Black;
            case Arcade::Color::RED:
                return sf::Color::Red;
            case Arcade::Color::GREEN:
                return sf::Color::Green;
            case Arcade::Color::YELLOW:
                return sf::Color::Yellow;
            case Arcade::Color::BLUE:
                return sf::Color::Blue;
            case Arcade::Color::PURPLE:
                return sf::Color::Magenta;
            case Arcade::Color::GREY:
                return sf::Color::Black;
            case Arcade::Color::WHITE:
                return sf::Color::White;
            default:
                return sf::Color::Black;
        }
    }

    void SFML::draw(std::shared_ptr<Arcade::Object> object)
    {
        if (object->getType() == Rectangle)
            drawRectangle(object);
        else if (object->getType() == Text)
            drawText(object);
        else if (object->getType() == Circle)
            drawCircle(object);
    }

    void SFML::drawRectangle(std::shared_ptr<Arcade::Object> object)
    {
        sf::Texture texture;
        sf::RectangleShape rectangle(sf::Vector2f(SIZE, SIZE));

        rectangle.setPosition(object->getPosition().getX() * SIZE, object->getPosition().getY() * SIZE);
        if (_textureMap.find(object->getAsset()) != _textureMap.end()) {
            rectangle.setTexture(&_textureMap[object->getAsset()]);
            _window.draw(rectangle);
        }
        if (object->getAsset().empty() == 0 && access(object->getAsset().c_str(), F_OK ) != -1 && texture.loadFromFile(object->getAsset())) {
            rectangle.setTexture(&texture);
            _textureMap[object->getAsset()] = texture;
        }
        else
            rectangle.setFillColor(defineColor(object->getColor()));
        _window.draw(rectangle);
    }

    void SFML::drawCircle(std::shared_ptr<Arcade::Object> object)
    {
        sf::Texture texture;
        sf::CircleShape Circle((float) SIZE / 2);

        Circle.setPosition(object->getPosition().getX() * SIZE, object->getPosition().getY() * SIZE);
        if (object->getAsset().empty() == 0 && access(object->getAsset().c_str(), F_OK ) != -1 && texture.loadFromFile(object->getAsset())) {
            Circle.setTexture(&texture);
        }
        else
            Circle.setFillColor(defineColor(object->getColor()));
        _window.draw(Circle);
    }

    void SFML::drawText(std::shared_ptr<Arcade::Object> object)
    {
        sf::Text sfText;
        sf::Font font;

        sfText.setString(object->getAsset());
        sfText.setPosition(object->getPosition().getX() * SIZE, object->getPosition().getY() * SIZE);
        sfText.setFillColor(defineColor(object->getColor()));
        if (font.loadFromFile(FONT)) {
            sfText.setFont(font);
        }
        _window.draw(sfText);
    }

    int SFML::playTurn()
    {
        sf::Time time = _clock.getElapsedTime();
        float s = time.asSeconds();

        if (s >= 0.3f) {
            _clock.restart();
            return static_cast<int>(s / 0.3f);
        }
        return 0;
    }

}

extern "C" Arcade::IDisplay *entryPointDisplay()
{
    return (new Arcade::SFML());
}
