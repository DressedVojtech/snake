#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

const float size = 20.0f;
const int areaSize = 30;

enum class directions {up, down, left, right};
//                     0    1      2     3

struct part {
    sf::Vector2i coords{};
};

class snake {
    private:
        std::vector<part> snake;
        directions dir = directions::up;
        bool ate;
    public:
        int lenght() {
            return snake.size();
        }
        void setDir(directions d) {
            dir = d;
        }
        sf::Vector2i body(int where) {
            return snake[where].coords;
        }
        void start(int x, int y) {
            snake.resize(2);
            snake[0].coords.x = x;
            snake[0].coords.y = y;
            snake[1].coords.x = (snake[1].coords.x) - 1;
            snake[1].coords.y = snake[1].coords.y;
        }
        void move() {
            for (int i = (snake.size()-1); i >= 1; i--) {
                snake[i] = snake [i - 1];
            }
            switch(dir) {
                case directions::up:
                    snake[0].coords.y -= 1;
                    //snake[0].coords.y = snake[0].coords.y;
                    break;
                case directions::down:
                    snake[0].coords.y += 1;
                    //snake[0].coords.y = snake[0].coords.y;
                    break;
                case directions::left:
                    //snake[0].coords.x = snake[0].coords.x;
                    snake[0].coords.x -= 1;
                    break;
                case directions::right:
                    //snake[0].coords.x = snake[0].coords.x;
                    snake[0].coords.x += 1;
                    break;
                default:
                    break;
            }
            if(snake[0].coords.x >= areaSize) {
                snake[0].coords.x = 0;
            }
            if(snake[0].coords.y >= areaSize) {
                snake[0].coords.y = 0;
            }
            if(snake[0].coords.x < 0) {
                snake[0].coords.x = (areaSize - 1);
            }
            if(snake[0].coords.y < 0) {
                snake[0].coords.y = (areaSize - 1);
            }
        }
};

int main() {
    snake s;
    s.start(10, 10);
    sf::RenderWindow window(sf::VideoMode((areaSize * size), (areaSize * size)), "snake", sf::Style::Close | sf::Style::Titlebar);
    sf::RectangleShape body(sf::Vector2f(size, size));
    body.setFillColor(sf::Color::Green);
    sf::RectangleShape apple(sf::Vector2f(size, size));
    apple.setFillColor(sf::Color::Red);

    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(e.key.code) {
                        case sf::Keyboard::Key::W:
                            s.setDir(directions::up);
                            break;
                        case sf::Keyboard::Key::S:
                            s.setDir(directions::down);
                            break;
                        case sf::Keyboard::Key::D:
                            s.setDir(directions::right);
                            break;
                        case sf::Keyboard::Key::A:
                            s.setDir(directions::left);
                            break;
                    }
            }
        }

    s.move();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    window.clear(sf::Color::Black);
    for (int i = areaSize; i >= 0; i--) {
        for (int j = areaSize; j >= 0; j--) {
            for (int a = s.lenght(); a >= 0 ;a--) {
                if ((s.body(a).x == i) && (s.body(a).y == j)) {
                    body.setPosition(i * size, j * size);
                    window.draw(body);
                }
            }
        }
    }
    window.display();
    }

}