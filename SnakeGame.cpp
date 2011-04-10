#include <iostream>

#include "SnakeGame.h"
#include "GamePiece.h"
#include "Food.h"
#include "Wall.h"

#define COLLISION_MAP_POINT(vector) m_collisionMap[vector.x][vector.y]

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

    for (std::list<GamePiece*>::iterator iter = m_lOtherPieces.begin(); iter != m_lOtherPieces.end(); iter++)
    {
        delete *iter;
    }
    m_lOtherPieces.clear();

    Food* food = new Food();
    food->place(m_collisionMap);
    m_lOtherPieces.push_back(food);

    for (int i = 0; i < 50; i++)
    {
        Wall* wall = new Wall();
        wall->place(m_collisionMap);
        m_lOtherPieces.push_back(wall);
    }

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

    sf::Vector2i headPosition, tailPosition;

    headPosition = m_snake.getHeadPosition();
    tailPosition = m_snake.getTailPosition();
    COLLISION_MAP_POINT(headPosition) ^= PIECE_SNAKE_HEAD;
    if (headPosition != tailPosition)
    {
        COLLISION_MAP_POINT(headPosition) |= PIECE_SNAKE_BODY;
        COLLISION_MAP_POINT(tailPosition) ^= PIECE_SNAKE_BODY;
    }

    m_snake.Move();

    headPosition = m_snake.getHeadPosition();
    tailPosition = m_snake.getTailPosition();
    COLLISION_MAP_POINT(headPosition) |= PIECE_SNAKE_HEAD;
    if (headPosition != tailPosition)
        COLLISION_MAP_POINT(tailPosition) |= PIECE_SNAKE_BODY;

    for (std::list<GamePiece*>::iterator iter = m_lOtherPieces.begin(); iter != m_lOtherPieces.end(); iter++)
    {
        (*iter)->Move();
    }

    checkCollisions();
}

void SnakeGame::checkCollisions()
{
    if (m_snake.isOutOfBounds())
    {
        m_bGameOver = true;
        return;
    }

    sf::Vector2i headPosition = m_snake.getHeadPosition();
    COLLISION_MAP_TYPE collisionValue = COLLISION_MAP_POINT(headPosition) ^ PIECE_SNAKE_HEAD;

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
