#include "SnakeGame.h"
#include <iostream>

const int FRAMES_PER_SECOND = 10;
const float SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
const int SLEEP_TICKS = 10;

SnakeGame::SnakeGame() : m_food(0, 0), m_viewRect(0.f, 0.f, MAP_DIMENSION, MAP_DIMENSION), m_bPaused(false), m_bGameOver(false)
{
    m_app.Create(sf::VideoMode(SCREEN_DIMENSION, SCREEN_DIMENSION), "Snake");
    sf::View view(m_viewRect);
    m_app.SetView(view);
    m_eUserDirection = CURRENT;

    std::srand(time(NULL));
    reset();
}

void SnakeGame::reset()
{
    for (int i = 0; i < PIXEL_LINE_COUNT; i++)
    {
        for (int j = 0; j < PIXEL_LINE_COUNT; j++)
        {
            m_collisionMap[i][j] = 0;
        }
    }

    placeFood();
    placeSnake();
    m_bGameOver = false;
}

void SnakeGame::run()
{
    sf::Clock Clock;

    float fpNextTick = Clock.GetElapsedTime() * 1000;

    while (1)
    {
        resetEvents();

        fpNextTick += SKIP_TICKS;
        while((Clock.GetElapsedTime() * 1000) < fpNextTick)
        {
            handleEvents();

            if (!m_app.IsOpened())
            {
                return;
            }

            sf::Sleep(SLEEP_TICKS / 1000);
        }

        if (!m_bPaused && !m_bGameOver)
        {
            updateGame();
            displayGame();
        }
    }
}

void SnakeGame::resetEvents()
{
    m_eUserDirection = CURRENT;
}

void SnakeGame::handleEvents()
{
    const sf::Input& Input = m_app.GetInput();
    if (Input.IsKeyDown(sf::Key::Up))
    {
        m_eUserDirection = UP;
    }
    else if (Input.IsKeyDown(sf::Key::Down))
    {
        m_eUserDirection = DOWN;
    }
    else if (Input.IsKeyDown(sf::Key::Left))
    {
        m_eUserDirection = LEFT;
    }
    else if (Input.IsKeyDown(sf::Key::Right))
    {
        m_eUserDirection = RIGHT;
    }

    sf::Event Event;
    while (m_app.GetEvent(Event))
    {
        if (Event.Type == sf::Event::Closed || (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape))
        {
            m_app.Close();
        }
        else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::P)
        {
            m_bPaused ^= true;
        }
        else if (m_bGameOver && Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::R)
        {
            reset();
        }
    }
}

void SnakeGame::updateGame()
{
    if (m_eUserDirection != CURRENT)
    {
        m_snake.ChangeDirection(m_eUserDirection);
    }

    int nHeadPosition[2];
    int nTailPosition[2];

    m_snake.getHeadPosition(nHeadPosition);
    m_snake.getTailPosition(nTailPosition);
    m_collisionMap[nHeadPosition[0]][nHeadPosition[1]] ^= PIECE_SNAKE_HEAD;
    if (nHeadPosition[0] != nTailPosition[0] || nHeadPosition[1] != nTailPosition[1])
    {
        m_collisionMap[nHeadPosition[0]][nHeadPosition[1]] |= PIECE_SNAKE_BODY;
        m_collisionMap[nTailPosition[0]][nTailPosition[1]] ^= PIECE_SNAKE_BODY;
    }

    m_snake.Move();

    // The head just entered this position
    m_snake.getHeadPosition(nHeadPosition);
    m_snake.getTailPosition(nTailPosition);
    m_collisionMap[nHeadPosition[0]][nHeadPosition[1]] |= PIECE_SNAKE_HEAD;
    if (nHeadPosition[0] != nTailPosition[0] || nHeadPosition[1] != nTailPosition[1])
        m_collisionMap[nTailPosition[0]][nTailPosition[1]] |= PIECE_SNAKE_BODY;

    m_food.Move();

    checkCollisions();
}

void SnakeGame::checkCollisions()
{
    if (m_snake.isOutOfBounds(m_viewRect))
    {
        m_bGameOver = true;
        return;
    }

    int nHeadPosition[2];
    m_snake.getHeadPosition(nHeadPosition);

    COLLISION_MAP_TYPE collisionValue = m_collisionMap[nHeadPosition[0]][nHeadPosition[1]] ^ PIECE_SNAKE_HEAD;
    if (isCollision(collisionValue, PIECE_FOOD))
    {
        SnakeSection* section = new SnakeSection();
        section->SetPosition(m_food.GetPosition());
        m_snake.addSection(*section);

        int nPosition[2];
        m_food.getPosition(nPosition);
        m_collisionMap[nPosition[0]][nPosition[1]] ^= PIECE_FOOD;

        placeFood();
    }
    else if (isCollision(collisionValue, PIECE_SNAKE_BODY))
    {
        m_bGameOver = true;
    }
}

bool SnakeGame::isCollision(COLLISION_MAP_TYPE collisionValue, COLLISION_MAP_TYPE checkAgainst)
{
    return ((collisionValue & checkAgainst) == checkAgainst);
}

void SnakeGame::displayGame()
{
    // Clear screen
    m_app.Clear(sf::Color::Black);

    m_app.Draw(m_snake);
    m_app.Draw(m_food);

    // Update the window
    m_app.Display();
}

void SnakeGame::placeFood()
{
    int nPosition[2];
    while (1)
    {
        m_food.randomizePosition();
        m_food.getPosition(nPosition);
        if (m_collisionMap[nPosition[0]][nPosition[1]] == PIECE_NONE)
        {
            m_collisionMap[nPosition[0]][nPosition[1]] = PIECE_FOOD;
            break;
        }
    }
}

void SnakeGame::placeSnake()
{
    m_snake.reset();
    m_collisionMap[0][0] = PIECE_SNAKE_HEAD;
}

void SnakeGame::placeWalls()
{

}
