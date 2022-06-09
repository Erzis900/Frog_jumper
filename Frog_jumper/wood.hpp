#ifndef WOOD_HPP
#define WOOD_HPP
#include <random>
#include <SFML/Graphics.hpp>

class Wood : public sf::RectangleShape
{
public:
    float speed = 1;

    Wood();
};

#endif // WOOD_HPP
