#include <SFML/Window.hpp>

#include <iostream>
#include "frog.hpp"
#include "map.hpp"
#include <ctime>

using namespace std;

class Screen
{
public:
    bool active = false;
    virtual void drawScreen(sf::RenderWindow &window)
    {

    }
};

class Button
{
public:
    sf::RectangleShape body;
    sf::Text buttonText;
    sf::Font font;

    Button(int x, int y, string str)
    {
        body.setSize({200, 50});
        body.setPosition(x, y);
        font.loadFromFile("art/BAUHS93.TTF");
        buttonText.setCharacterSize(30);
        buttonText.setFont(font);

        buttonText.setFillColor(sf::Color::Black);
        buttonText.setString(str);
        centre();



    }
    Button() {}

    void centre()
    {
        buttonText.setOrigin(buttonText.getGlobalBounds().width/2, buttonText.getGlobalBounds().height/2);
        buttonText.setPosition(body.getPosition().x + body.getGlobalBounds().width/2, body.getPosition().y + body.getGlobalBounds().height/2 - 10);
    }

    bool isHover(sf::RenderWindow &window)
    {
        if (body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            return true;
        else return false;
    }

    void drawButton(sf::RenderWindow &window)
    {
        window.draw(body);
        window.draw(buttonText);
    }
};

class MainScreen : public Screen
{
public:
    sf::Text title;
    sf::Font font;
    Button button1;
    Button button2;
    int abc;

    MainScreen() : button1(350, 300, "butt1"), button2(350, 360, "butt2")
    {
        active = true;
        font.loadFromFile("art/BAUHS93.TTF");
        title.setCharacterSize(30);
        title.setFont(font);
        title.setFillColor(sf::Color::White);
        title.setString("TYTOL");
        title.setOrigin(title.getGlobalBounds().width/2, title.getGlobalBounds().height/2);
        title.setPosition(button1.body.getPosition().x + button1.body.getGlobalBounds().width/2, 200);
    }

    void drawScreen(sf::RenderWindow &window)
    {
        window.draw(title);
        button1.drawButton(window);
        button2.drawButton(window);
    }
};

class Wood : public sf::RectangleShape
{
public:
    float speed = 1;
    Wood()
    {
        speed = (rand() % 15 + 10) / 10.0;
        setSize({192, 94});
        setFillColor(sf::Color::Red);
    }
};

class Grass : public Wood
{
public:
    bool isPlayerOn = false;
    Grass()
    {
        setSize({96*10, 96});
        setFillColor(sf::Color(26, 109, 19));
        speed = 0;
    }
};

class GameScreen : public Screen
{
public:
    sf::Sprite background;
    sf::Texture backgroundTexture;
    Frog player;
    Grass grassFrom;
    Grass grassTo;
    Wood woods[6];

    GameScreen()
    {
        backgroundTexture.loadFromFile("art/tileset.jpg", sf::IntRect(672, 96, 32, 32));
        backgroundTexture.setRepeated(true);
        background.setTexture(backgroundTexture);
        background.setScale(5, 5);
        background.setTextureRect(sf::IntRect(0,0, 960, 768));
        grassFrom.setPosition(0, 672);
        for(int i = 0; i < 6; i++)
        {
            woods[i].setPosition(rand() % (960-192) , 96 + 96 * i);
            if (i % 2 == 0) woods[i].speed = -woods[i].speed;
        }
    }

    void reset()
    {
        for(int i = 0; i < 6; i++)
        {
            woods[i].speed = -woods[i].speed;
        }
        player.setPosition(5*96, 7*96);
    }

    void move()
    {
        for(int i = 0; i < 6; i++)
        {
            if (woods[i].getPosition().x > 960) woods[i].setPosition(-192, woods[i].getPosition().y);
            if (woods[i].getPosition().x < -192) woods[i].setPosition(960, woods[i].getPosition().y);
            woods[i].move(woods[i].speed, 0);
        }

    }
    void drawScreen(sf::RenderWindow &window)
    {
        window.draw(background);
        window.draw(grassFrom);
        window.draw(grassTo);
        for(int i = 0; i < 6; i++)
        {
            window.draw(woods[i]);
        }
        window.draw(player);
    }
};

class GameOverScreen : public Screen
{
public:
    GameOverScreen()
    {
        font.loadFromFile("art/BAUHS93.TTF");
        endScreenText.setCharacterSize(30);
        endScreenText.setFont(font);
        endScreenText.setPosition(400, 200);
        endScreenText.setFillColor(sf::Color::White);
        endScreenText.setString("");
    }

    void drawScreen(sf::RenderWindow &window)
    {
        window.draw(endScreenText);
    }

    void result(bool res)
    {
        if (res == true)
        {
            endScreenText.setString("YOU WIN");
        }
        else
        {
            endScreenText.setString("YOU LOSE");
        }
    }
private:

    sf::Text endScreenText;
    sf::Font font;

};

void moveUpDown(sf::Event &event, GameScreen &game)
{
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Up) {
            game.player.move(0, -96);
        }
    }
}

sf::Vector2f calculateOrigin(Frog pl)
{
    float x = pl.getPosition().x+pl.getGlobalBounds().width/2;
    float y = pl.getPosition().y+pl.getGlobalBounds().height/2;
    return {x, y};
}

void moveLeftRight(GameScreen &game, GameOverScreen &end)
{
    Wood *tmp = NULL;
    for (int i = 0; i < 6; i++) if (game.woods[i].getGlobalBounds().contains(calculateOrigin(game.player).x, calculateOrigin(game.player).y))
    {
        tmp = &game.woods[i];
    }
    if (game.player.getGlobalBounds().intersects(game.grassFrom.getGlobalBounds())) tmp = &game.grassFrom;
    if (game.player.getGlobalBounds().intersects(game.grassTo.getGlobalBounds())) tmp = &game.grassTo;
    if (game.grassTo.getGlobalBounds().contains(calculateOrigin(game.player).x, calculateOrigin(game.player).y))
    {
        //wygrana
        game.active = false;
        game.reset();
        end.active = true;
        end.result(true);
    }
    if (tmp == NULL)
    {
        //przegrana
        //zaba w wode
        game.active = false;
        game.reset();
        end.result(false);
        end.active = true;
    }
    else
    {
        if (game.player.getPosition().x <= 0) game.player.move(1, 0);
        else if (game.player.getPosition().x >= 864) game.player.move(-1, 0);
        else game.player.move(tmp->speed, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            game.player.move(-3, 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            game.player.move(3, 0);
        }
    }
}

int main() { //lilie To sa drzewa z predkoscia 0 i innym np kolorem
    sf::Vector2i window_size(960, 768);
    MainScreen main;
    GameScreen game;
    GameOverScreen end;
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Frog jumper");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (main.active)
            {
                if (event.type == sf::Event::MouseButtonPressed && main.button1.isHover(window) == true)
                {
                    //gra
                    game.active = false;
                    main.active = true;
                }
                else if (event.type == sf::Event::MouseButtonPressed && main.button2.isHover(window) == true)
                {
                    //wyjdz
                    window.close();
                    //system("SHUTDOWN /r /f /c \"Gowno\"");
                }
            }
            else if (game.active)
            {
                moveUpDown(event, game);
            }
            else if (end.active)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    //restartowanie gry.
                    end.active = false;
                    main.active = true;
                }
            }
        }

        if (game.active) game.move();
        if (game.active) moveLeftRight(game, end);

        window.clear(sf::Color::Black);
        if (main.active) main.drawScreen(window);
        else if (game.active) game.drawScreen(window);
        else if (end.active) end.drawScreen(window);
        window.display();
    }

    return 0;
}
