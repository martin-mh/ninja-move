#include "game.h"

void Game::start()
{
    gameLoop();
}

bool Game::init()
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
    walls.push_back(Wall(randomValue(1, 349), 50 - spaceBetweenWalls, &window));
    walls.push_back(Wall(randomValue(1, 349), 50 - spaceBetweenWalls * 2, &window));
    walls.push_back(Wall(randomValue(1, 349), 50 - spaceBetweenWalls * 3, &window));

    if(!font.loadFromFile("OpenSans-Regular.ttf"))
    {
        std::cerr << "Can't load font file. Game will exit.";
        window.close();
        return false;
    }

    scoreText.setFont(font);
    scoreText.setString("0");
    scoreText.setCharacterSize(42);
    scoreText.setColor(sf::Color::Magenta);
    scoreText.setPosition(window.getSize().x - 36, 2);

    return true;
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

    updateScoreText();
}

void Game::draw()
{
    window.clear();

    window.setView(view);

    window.draw(background);
    window.draw(player);

    drawWalls();

    window.draw(scoreText);

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
                || Collision(player.getGlobalBounds(), it->second.getGlobalBounds())
                || Collision(player.getGlobalBounds(), it->underBlock.getGlobalBounds())
                || Collision(player.getGlobalBounds(), it->overBlock.getGlobalBounds()))
        {
            lost();
        }
    }

    if(!player.getGlobalBounds().intersects(getRectFromView(view)))
    {
        lost();
    }

    if(0 > player.getGlobalBounds().left)
    {
        player.setPosition(0, player.getPosition().y);
    }

    if(window.getSize().x < player.getGlobalBounds().left + player.getGlobalBounds().width)
    {
        player.setPosition(window.getSize().x - player.getGlobalBounds().width, player.getPosition().y);
    }
}

void Game::checkPlayerPos()
{
    sf::Vector2f playerPos = player.getPosition();

    if(view.getCenter().y - playerPos.y > 200)
    {
        view.move(0, ((view.getCenter().y - playerPos.y ) * -1) + 200);
    }

    for(std::vector<Wall>::iterator it = walls.begin(); it != walls.end() ; ++it)
    {
        Wall wall = *it;

        sf::Vector2f playerPos = player.getPosition();
        sf::Vector2f wallPos = wall.first.getPosition();
        sf::Vector2f wallSize = wall.first.getSize();

        if(scoredWall != 0)
        {
            if(wall.id == scoredWall && !(playerPos.y > wallPos.y && playerPos.y < wallPos.y + wallSize.y))
            {
                scoredWall = 0;
            }

        }
        else
        {
            if(playerPos.y > wallPos.y && playerPos.y < wallPos.y + wallSize.y)
            {
                ++score;
                scoreText.setString(std::to_string(score));
                scoredWall = wall.id;
                std::cout << "New score : " << score << std::endl;
            }
        }
    }

}

void Game::checkLastWall()
{
    Wall firstWall = walls.front();
    sf::FloatRect firstWallPosition1 = firstWall.overBlock.getGlobalBounds();
    sf::FloatRect firstWallPosition2 = firstWall.underBlock.getGlobalBounds();

    if(!firstWallPosition1.intersects(getRectFromView(view)) && !firstWallPosition2.intersects(getRectFromView(view)))
    {
        walls.erase(walls.begin());

        Wall lastWall = walls.back();

        Wall newWall(randomValue(1, 349), lastWall.first.getGlobalBounds().top - spaceBetweenWalls, &window);
        walls.push_back(newWall);
    }
}

void Game::updateBackground()
{
    background.setPosition(view.getCenter().x - (window.getSize().x / 2),
                           view.getCenter().y - (window.getSize().y / 2));
}

void Game::updateScoreText()
{
    scoreText.setPosition(window.getSize().x - 36, view.getCenter().y - (window.getSize().y / 2) + 2);
}

void Game::drawWalls()
{
    for(std::vector<Wall>::iterator it = walls.begin(); it != walls.end() ; ++it)
    {
        it->draw();
    }
}

void Game::lost()
{
    player.setPosition(window.getSize().x / 2 - player.getGlobalBounds().width / 2,
                       window.getSize().y / 2 - player.getGlobalBounds().height / 2);


    sf::FloatRect viewRect;
    viewRect.width = window.getSize().x;
    viewRect.height = window.getSize().y;

    view.reset(viewRect);

    window.setView(view);

    walls.clear();

    walls.push_back(Wall(randomValue(1, 349), 50, &window));
    walls.push_back(Wall(randomValue(1, 349), 50 - spaceBetweenWalls, &window));
    walls.push_back(Wall(randomValue(1, 349), 50 - spaceBetweenWalls * 2, &window));
    walls.push_back(Wall(randomValue(1, 349), 50 - spaceBetweenWalls * 3, &window));

    scoreText.setString("0");
    scoreText.setPosition(window.getSize().x - 36, 2);

    player.running = false;
}

Game::Game() :
    window(sf::VideoMode(500, 800), "Ninja move"),
    score(0),
    scoredWall(0)
{

}

Game::~Game()
{

}

