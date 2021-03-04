#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(650.0f, 650.0f), "Snake 1.0", sf::Style::Close | sf::Style::Titlebar);

    while(window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch(evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

    window.clear(sf::Color::Black);
    window.display();
    }

    return 0;
}