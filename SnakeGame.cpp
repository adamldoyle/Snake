#include "SnakeGame.h"
#include <iostream>

const int FRAMES_PER_SECOND = 10;
const float SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
const int SLEEP_TICKS = 10;

SnakeGame::SnakeGame() : m_viewRect(0.f, 0.f, MAP_DIMENSION, MAP_DIMENSION), m_bPaused(false), m_bGameOver(false)//, m_food(0, 0)
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

    placeSnake();

    m_lOtherPieces.clear();
    Food* food = new Food();
    food->place(m_collisionMap);
    m_lOtherPieces.push_back(food);

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

    m_snake.getHeadPosition(nHeadPosition);
    m_snake.getTailPosition(nTailPosition);
    m_collisionMap[nHeadPosition[0]][nHeadPosition[1]] |= PIECE_SNAKE_HEAD;
    if (nHeadPosition[0] != nTailPosition[0] || nHeadPosition[1] != nTailPosition[1])
        m_collisionMap[nTailPosition[0]][nTailPosition[1]] |= PIECE_SNAKE_BODY;

    for (std::list<GamePiece*>::iterator iter = m_lOtherPieces.begin(); iter != m_lOtherPieces.end(); iter++)
    {
        (*iter)->Move();
    }

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

    if (isCollision(collisionValue, PIECE_SNAKE_BODY))
    {
        m_bGameOver = true;
        return;
    }

    for (std::list<GamePiece*>::iterator iter = m_lOtherPieces.begin(); iter != m_lOtherPieces.end(); iter++)
    {
        if (isCollision(collisionValue, (*iter)->getPieceType()))
        {
            if ((*iter)->handleCollision(m_snake, m_collisionMap))
            {
                m_bGameOver = true;
                return;
            }
        }
    }
}

bool SnakeGame::isCollision(COLLISION_MAP_TYPE collisionValue, COLLISION_MAP_TYPE checkAgainst)
{
    return ((collisionValue & checkAgainst) == checkAgainst);
}

void SnakeGame::displayGame()
{
    m_app.Clear(sf::Color::Black);

    m_app.Draw(m_snake);
    for (std::list<GamePiece*>::iterator iter = m_lOtherPieces.begin(); iter != m_lOtherPieces.end(); iter++)
    {
        m_app.Draw(**iter);
    }

    m_app.Display();
}

void SnakeGame::placeSnake()
{
    m_snake.reset();
    m_collisionMap[0][0] = PIECE_SNAKE_HEAD;
}
