#ifndef FROG_HPP
#define FROG_HPP

#include <SFML/Graphics.hpp>

class Frog : public sf::RectangleShape {
public:
    Frog();

    void handle_movement(sf::Keyboard::Key key);
    void check_borders(sf::Vector2i window_size);
private:
    sf::Vector2f size;
    sf::Vector2f pos;
};

#endif // FROG_HPP
