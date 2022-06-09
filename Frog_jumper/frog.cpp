#include "frog.hpp"

Frog::Frog() {
    tex.loadFromFile("art/frog.png");
    setTexture(tex);

    size.x = 96;
    size.y = 94;

    pos.x = 5*96;
    pos.y = 7*96;

    setScale(0.48, 0.47);
    setPosition(pos);
}

void Frog::handle_movement(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::Up) {
        pos.y -= size.y;
    }
    else if(key == sf::Keyboard::Down) {
        pos.y += size.y;
    }
    else if(key == sf::Keyboard::Left) {
        pos.x -= size.x;
    }
    else if(key == sf::Keyboard::Right) {
        pos.x += size.x;
    }

    setPosition(pos);
}

void Frog::check_borders(sf::Vector2i window_size) {
    if(pos.x < 0) pos.x = 0;
    else if(pos.x > window_size.x - size.x) pos.x = window_size.x - size.x;
    else if(pos.y < 0) pos.y = 0;
    else if(pos.y > window_size.y - size.y) pos.y = window_size.y - size.y;

    setPosition(pos);
}
