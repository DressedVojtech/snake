#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <stdlib.h>

const float size = 20.0f;
const int areaSize = 15;
int cooldown = 1000;
int score;

enum class fruits {apple, banana, melon, orange, pineapple};
//                  0       1       2       3       4
enum class directions {up, down, left, right};
//                     0    1      2     3

struct part {
    sf::Vector2i coords{};
};

struct apples {
    sf::Vector2i coords{};
    fruits current;
};

class snake {
    private:
        std::vector<part> snake;
        directions dir = directions::up;
        bool ate;
        apples apple;

    public:
        int lenght() {
            return snake.size();
        }
        directions direction() {
            return dir;
        }
        fruits seeCurrent() {
            return apple.current;
        }
        void setApple() {
            srand(time(0));
            int x = rand()%(areaSize-1);
            int y = rand()%(areaSize-1);

            apple.coords.x = x;
            apple.coords.y = y;
            int current = rand()%5;
            switch (current) {
                case 0:
                    apple.current = fruits::apple;
                    break;
                case 1:
                    apple.current = fruits::banana;
                    break;
                case 2:
                    apple.current = fruits::melon;
                    break;
                case 3:
                    apple.current = fruits::orange;
                    break;
                case 4:
                    apple.current = fruits::pineapple;
                    break;
            }
        }
        sf::Vector2i seeApple() {
            return apple.coords;
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
            setApple();
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
            for (int i = snake.size(); i > 0; i--) {
                if (snake[i].coords == snake[0].coords) {
                    std::cout << "GAME OVER - your snake ate itself" << std::endl;
                    std::cout << "YOUR SCORE IS: " << score << std::endl;
                    exit(0);
                }
            }

            if (snake[0].coords == seeApple()) {
                snake.push_back({
                    .coords = sf::Vector2i(-2, -2)
                });
                setApple();
                score++;
            }
        }
};

int main() {
    snake s;
    s.start(10, 10);
    sf::RenderWindow window(sf::VideoMode((areaSize * size), (areaSize * size)), "snake", sf::Style::Close | sf::Style::Titlebar);
    
    sf::RectangleShape body(sf::Vector2f(size -3, size - 3));
    body.setFillColor(sf::Color::Green);

    sf::RectangleShape apple(sf::Vector2f(size, size));
    sf::RectangleShape banana(sf::Vector2f(size, size));
    sf::RectangleShape melon(sf::Vector2f(size, size));
    sf::RectangleShape orange(sf::Vector2f(size, size));
    sf::RectangleShape pineapple(sf::Vector2f(size, size));

    sf::Texture appleTexture;
    sf::Texture bananaTexture;
    sf::Texture melonTexture;
    sf::Texture orangeTexture;
    sf::Texture pineappleTexture;

    appleTexture.loadFromFile("Textures/apple.png");
    bananaTexture.loadFromFile("Textures/banana.png");
    melonTexture.loadFromFile("Textures/melon.png");
    orangeTexture.loadFromFile("Textures/orange.png");
    pineappleTexture.loadFromFile("Textures/pineapple.png");

    apple.setTexture(&appleTexture);
    banana.setTexture(&bananaTexture);
    melon.setTexture(&melonTexture);
    orange.setTexture(&orangeTexture);
    pineapple.setTexture(&pineappleTexture);

    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                    std::cout << "YOUR SCORE IS: " << score << std::endl;
                    break;
                case sf::Event::KeyPressed:
                    switch(e.key.code) {
                        case sf::Keyboard::Key::W:
                            if (s.direction() != directions::down) {
                                s.setDir(directions::up);
                            }
                            break;
                        case sf::Keyboard::Key::Up:
                            if (s.direction() != directions::down) {
                                s.setDir(directions::up);
                            }
                            break;
                        case sf::Keyboard::Key::S:
                            if (s.direction() != directions::up) {
                                s.setDir(directions::down);
                            }
                            break;
                        case sf::Keyboard::Key::Down:
                            if (s.direction() != directions::up) {
                                s.setDir(directions::down);
                            }
                            break;
                        case sf::Keyboard::Key::D:
                            if (s.direction() != directions::left) {
                                s.setDir(directions::right);
                            }
                            break;
                            case sf::Keyboard::Key::Right:
                            if (s.direction() != directions::left) {
                                s.setDir(directions::right);
                            }
                            break;
                        case sf::Keyboard::Key::A:
                            if (s.direction() != directions::right) {
                                s.setDir(directions::left);
                            }
                            break;
                        case sf::Keyboard::Key::Left:
                            if (s.direction() != directions::right) {
                                s.setDir(directions::left);
                            }
                            break;
                    }
            }
        }
    s.move();

    std::this_thread::sleep_for(std::chrono::milliseconds(cooldown));
    if (cooldown >= 100) {
            cooldown -= 0.001 * cooldown;
    }

    window.clear(sf::Color::Black);
    
            if (s.seeCurrent() == fruits::apple) {
            apple.setPosition(s.seeApple().x * size, s.seeApple().y * size);
            window.draw(apple);
            }
            if (s.seeCurrent() == fruits::banana) {
            banana.setPosition(s.seeApple().x * size, s.seeApple().y * size);
            window.draw(banana);
            }
            if (s.seeCurrent() == fruits::melon) {
            melon.setPosition(s.seeApple().x * size, s.seeApple().y * size);
            window.draw(melon);
            }
            if (s.seeCurrent() == fruits::orange) {
            orange.setPosition(s.seeApple().x * size, s.seeApple().y * size);
            window.draw(orange);
            }
            if (s.seeCurrent() == fruits::pineapple) {
            pineapple.setPosition(s.seeApple().x * size, s.seeApple().y * size);
            window.draw(pineapple);
            }
            for(int a = 0; a < s.lenght(); a++) {
            body.setPosition(s.body(a).x * size,s.body(a).y * size);
            window.draw(body);
            }
    window.display();
    }
}