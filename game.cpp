#include "game.h"

void Game::start()
{
    gameLoop();
}

void Game::init()
{
    window.setFramerateLimit(60);

    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color::White);

    player.setPosition(window.getSize().x / 2 - player.getGlobalBounds().width / 2,
                       window.getSize().y / 2 - player.getGlobalBounds().height / 2);


    sf::FloatRect viewRect;
    viewRect.width = window.getSize().x;
    viewRect.height = window.getSize().y;

    view.reset(viewRect);

    window.setView(view);

    walls.push_back(Wall(randomValue(1, 349), 50, &window));
    walls.push_back(Wall(randomValue(1, 349), -350, &window));
    walls.push_back(Wall(randomValue(1, 349), -750, &window));
}

void Game::gameLoop()
{
    while (window.isOpen())
    {
        computeGameLogic();

        draw();

        std::this_thread::sleep_for(std::chrono::seconds(1)/60);
    }
}

void Game::computeGameLogic()
{
    checkLastWall();

    pollEvents();

    player.update();

    checkPlayerPos();

    computeCollisions();

    updateBackground();
}

void Game::draw()
{
    window.clear();

    window.setView(view);

    window.draw(background);
    window.draw(player);

    drawWalls();

    window.display();
}

void Game::pollEvents()
{
    sf::Event event;

    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.left();
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.right();
    }
}

void Game::computeCollisions()
{
    for(std::vector<Wall>::iterator it = walls.begin(); it != walls.end() ; ++it)
    {
        if(Collision(player.getGlobalBounds(), it->first.getGlobalBounds())
                || Collision(player.getGlobalBounds(), it->second.getGlobalBounds()))
        {
            window.close();
        }
    }

    if(!player.getGlobalBounds().intersects(getRectFromView(view)))
    {
        window.close();
    }
}

void Game::checkPlayerPos()
{
    sf::Vector2f playerPos = player.getPosition();

    if(view.getCenter().y - playerPos.y > 200)
    {
        view.move(0, ((view.getCenter().y - playerPos.y ) * -1) + 200);
    }

}

void Game::checkLastWall()
{
    Wall firstWall = walls.front();
    sf::FloatRect firstWallPosition = firstWall.first.getGlobalBounds();

    if(!firstWallPosition.intersects(getRectFromView(view)))
    {
        walls.erase(walls.begin());

        Wall lastWall = walls.back();

        Wall newWall(randomValue(1, 349), lastWall.first.getGlobalBounds().top - 400, &window);
        walls.push_back(newWall);

        std::cout << lastWall.first.getGlobalBounds().top << std::endl;
    }
}

void Game::updateBackground()
{
    background.setPosition(view.getCenter().x - (window.getSize().x / 2),
                           view.getCenter().y - (window.getSize().y / 2));
}

void Game::drawWalls()
{
    for(std::vector<Wall>::iterator it = walls.begin(); it != walls.end() ; ++it)
    {
        it->draw();
    }
}

Game::Game() :
    window(sf::VideoMode(500, 800), "Ninja move")
{

}

Game::~Game()
{

}

