#include "wood.hpp"

Wood::Wood()
{
    speed = (rand() % 15 + 10) / 10.0;
    setSize({192, 94});
    setFillColor(sf::Color::Cyan);
}
