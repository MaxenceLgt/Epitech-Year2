/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Object.hpp
*/


#pragma once

#include <iostream>
#include "Color.hpp"

/**
** @file IObject.hpp
** @brief IObject class for the Arcade project
**/
namespace Arcade {
    
    /**
    * @enum Type
    * @brief An enumeration to standardize types across libraries.
    *
    * This enumeration contains all possible types that can be used in the Arcade project.
    */
    enum Type {
        Circle, ///< Represents a circle
        Rectangle, ///< Represents a rectangle
        Text, ///< Represents a text
        Unknown ///< Represents an unknown type
    };

    /**
    * @class IObject
    * @brief A class to represent an object in the Arcade project.
    *
    * This class contains a position, a type, and a color to represent an object in the Arcade project.
    */
    class Object {
        public:
            /**
            * @class Position
            * @brief A class to represent a position in a 2D space.
            *
            * This class contains two integers, x and y, to represent a position in a 2D space.
            */
            class Position {
                public:
                    /**
                    * @brief Construct a new Position object with x and y coordinates set to 0.
                    *
                    * @return A new Position object with x and y coordinates set to 0.
                    */
                    Position(int x, int y) : x(x), y(y) {};

                    /**
                    * @brief Construct a new Position object with given x and y coordinates.
                    *
                    * @param x The x coordinate of the position.
                    * @param y The y coordinate of the position.
                    */
                    Position(const Position &pos) : x(pos.x), y(pos.y) {};

                public:
                    /**
                    * @brief Copy constructor for the Position class.
                    *
                    * This constructor creates a new Position object by copying the x and y coordinates from another Position object.
                    *
                    * @param pos The Position object to copy from.
                    */
                    Position& operator=(const Position &pos) {
                        if (this != &pos) {
                            x = pos.x;
                            y = pos.y;
                        }
                        return *this;
                    };

                public:
                    /**
                    * @brief Set the X coordinate of the position.
                    *
                    * @param x The new X coordinate.
                    */
                    void setX(int x) {this->x = x;};

                    /**
                    * @brief Set the Y coordinate of the position.
                    *
                    * @param y The new Y coordinate.
                    */
                    void setY(int y) {this->y = y;};

                    /**
                    * @brief Get the X coordinate of the position.
                    *
                    * @return The X coordinate.
                    */
                    int getX() const {return x;};

                    /**
                    * @brief Get the Y coordinate of the position.
                    *
                    * @return The Y coordinate.
                    */
                    int getY() const {return y;};
                private:
                    int x; ///< The X coordinate of the position.
                    int y; ///< The Y coordinate of the position.
            };

        public:
            /**
            * @brief Construct a new Object object with given position, type, and color.
            *
            * @param position The position of the object.
            * @param type The type of the object.
            * @param color The color of the object.
            */
            Object(const Position &position, const Type &type, const Color &color) : _position(position), _type(type), _color(color) {};

            /**
            * @brief Construct a new Object object with given x and y coordinates, type, and color.
            *
            * @param x The x coordinate of the position.
            * @param y The y coordinate of the position.
            * @param type The type of the object.
            * @param color The color of the object.
            */
            Object(const int x, const int y, const Type &type, const Color &color) : _position(x, y), _type(type), _color(color) {};

            /**
            * @brief Construct a new Object object with given x and y coordinates, type, and color.
            *
            * @param x The x coordinate of the position.
            * @param y The y coordinate of the position.
            * @param type The type of the object.
            * @param color The color of the object.
            * @param asset The asset of the object.
            */
            Object(const int x, const int y, const Type &type, const Color &color, std::string asset) : _position(x, y), _type(type), _color(color), _asset(asset) {};

            /**
            * @brief Construct a new Object object with given position, type, and color.
            *
            * @param position The position of the object.
            * @param type The type of the object.
            * @param color The color of the object.
            * @param asset The asset of the object.
            */
            Object(const Position &position, const Type &type, const Color &color, std::string asset) : _position(position), _type(type), _color(color), _asset(asset) {};

            /**
             * @brief Destructor of Object object
            */
            ~Object() {};

        public:
            /**
            * @brief Get the Position of the object.
            *
            * This is a pure virtual function that needs to be implemented by any class that inherits from IObject.
            *
            * @return The Position of the object.
            */
            Position getPosition() const {return _position;};

            /**
            * @brief Set the Position of the object.
            *
            * This is a pure virtual function that needs to be implemented by any class that inherits from IObject.
            *
            * @param newPosition The new Position of the object.
            */
            void setPosition(const Position newPosition) {_position = newPosition;};

            /**
            * @brief Set the Position of the object.
            *
            * This is a pure virtual function that needs to be implemented by any class that inherits from IObject.
            *
            * @param x The new x-coordinate of the object.
            * @param y The new y-coordinate of the object.
            */
            void setPosition(const int x, const int y) {_position.setX(x); _position.setY(y);};

            /**
            * @brief Get the Type of the object.
            *
            * This is a pure virtual function that needs to be implemented by any class that inherits from IObject.
            *
            * @return The Type of the object.
            */
            Type getType() {return _type;};

            /**
            * @brief Get the Color of the object.
            *
            * This is a pure virtual function that needs to be implemented by any class that inherits from IObject.
            *
            * @return The Color of the object.
            */
            Color getColor() {return _color;};

            /**
            * @brief Set the Color of the object.
            *
            * This is a pure virtual function that needs to be implemented by any class that inherits from IObject.
            *
            * @param color The new Color of the object.
            */
            void setColor(Color color) {_color = color;};

            /**
            * @brief Set the asset of the object.
            *
            * This is a pure virtual function that needs to be implemented by any class that inherits from IObject.
            *
            * @param asset The new asset of the object.
            */
            void setAsset(std::string asset) {_asset = asset;};

            /**
            * @brief Get the asset of the object.
            *
            * This is a pure virtual function that needs to be implemented by any class that inherits from IObject.
            *
            * @return The asset of the object.
            */
            std::string getAsset() {return _asset;};

            /**
            * @brief Check if the asset is set.
            *
            * This is a pure virtual function that needs to be implemented by any class that inherits from IObject.
            *
            * @return True if the asset is set, false otherwise.
            */
            bool assetIsSet() {return !_asset.empty();};
        private:
            Position _position; ///< The position of the object.
            Type _type; ///< The type of the object.
            Color _color; ///< The color of the object.
            std::string _asset; ///< The asset of the object.
    };
}
