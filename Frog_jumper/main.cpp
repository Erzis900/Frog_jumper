#include <SFML/Window.hpp>

#include <iostream>
#include "frog.hpp"

int main() {
    sf::Vector2i window_size(800, 600);

    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Frog jumper");

    Frog frog;

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

        window.clear(sf::Color::Black);

        window.draw(frog);

        window.display();
    }

    return 0;
}
