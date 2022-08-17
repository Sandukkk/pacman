#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <map.h>
#include <player.h>


#include <string>

class Window :public sf::RenderWindow
{
    int width, height, colors;
    std::string name;

public:
    Window(std::string, int, int, int);
};
#include <window.h>
#include <SFML/Graphics.hpp>
#include <string>
#include "map.h"
class Player
{
    sf::Sprite sprite;
    int posX;
    int posY;
    std::string direction;
    bool isMoving;


public:
    std::string directionToCheck;
    Player(sf::Texture&, sf::Sprite, sf::IntRect, int, int);
    void checkColAndMove(std::vector <Tile>, int pix = 2);
    void draw(sf::RenderWindow& window);
    bool checkCollision(std::vector <Tile>);
    void setDirection(std::string);
    std::string getDirection();
    void move(int);
    void setFace(std::string);
    void chooseDirection(std::string);
    int getPosY();
    int getPosX();
    //void turn(std::string);
};
int main()
{
    //SPRITESHEET
    sf::Texture spriteSheet;
    spriteSheet.loadFromFile("spriteSheet.png");

    //SPRITES
    sf::Sprite ghost;
    sf::Sprite tileSprite;

    //OBJECTS
    Player pacman(spriteSheet, ghost, sf::IntRect(0, 0, 64, 64), 32, 32);
    Map map;

    //WINDOW
    Window appWindow("Pacman", 1280, 1024, 32);
    appWindow.setFramerateLimit(60);
    appWindow.setVerticalSyncEnabled(true);

    while (appWindow.isOpen()) //MAIN LOOP
    {
        sf::Event event;
        while (appWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                appWindow.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            {
                pacman.chooseDirection("right");
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            {
                pacman.chooseDirection("left");
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                pacman.chooseDirection("up");
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                pacman.chooseDirection("down");
            }
        }
        pacman.move(4);
        pacman.checkColAndMove(map.getTilemap(), 4);

        appWindow.clear(sf::Color::Black);

        map.generate(appWindow, spriteSheet, 264); //298 - red tiles, 264 (default value) - blue tiles
        pacman.draw(appWindow);
        appWindow.display();
        sf::sleep(sf::microseconds(50));
    }
    return 0;
}

// TO DO
// - make movement and collisions using classes
// - make second map
// - make player a pacman instead of ghost
// - make ghosts with ai
// - make player choose direction before hitting the wall
