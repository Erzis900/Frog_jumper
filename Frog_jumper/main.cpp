#include <SFML/Window.hpp>

#include <iostream>
#include "frog.hpp"
#include "map.hpp"

int main() {
    sf::Vector2i window_size(960, 768);

    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Frog jumper");

    Map map;
    Frog frog;

    const int level[] =
    {
        90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
        90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
        90, 90, 90, 90, 90, 64, 90, 90, 90, 90,
        64, 64, 64, 64, 90, 90, 64, 64, 64, 90,
        90, 90, 90, 64, 64, 64, 64, 90, 64, 64,
        90, 90, 90, 90, 90, 64, 90, 64, 90, 90,
        90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
        90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
    };

    if (!map.load("../Frog_Jumper/art/tileset.jpg", sf::Vector2u(32, 32), level, 10, 8))
        return -1;

    map.setScale(3, 3);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyReleased) {
                if(event.key.code == sf::Keyboard::Up) {
                    frog.handle_movement(sf::Keyboard::Up);
                }
                else if(event.key.code == sf::Keyboard::Down) {
                    frog.handle_movement(sf::Keyboard::Down);
                }
                else if(event.key.code == sf::Keyboard::Left) {
                    frog.handle_movement(sf::Keyboard::Left);
                }
                else if(event.key.code == sf::Keyboard::Right) {
                    frog.handle_movement(sf::Keyboard::Right);
                }

                frog.check_borders(window_size);
            }
        }

        window.clear(sf::Color::Blue);

        window.draw(map);
        window.draw(frog);

        window.display();
    }

    return 0;
}
