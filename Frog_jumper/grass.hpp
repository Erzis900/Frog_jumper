#ifndef GRASS_HPP
#define GRASS_HPP
#include "wood.hpp"

class Grass : public Wood
{
public:
    bool isPlayerOn = false;
    Grass();
private:
    sf::Texture tex;
};

#endif // GRASS_HPP
