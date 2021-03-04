#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(700.0f, 700.0f), "Snake 1.0");

    while(window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch(evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

    window.clear(sf::Color::White);
    window.display();
    }

    return 0;
}