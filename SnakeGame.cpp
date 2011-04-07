#include "SnakeGame.h"

const int FRAMES_PER_SECOND = 10;
const float SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
const int SLEEP_TICKS = 10;

SnakeGame::SnakeGame() : m_food(0, 0), m_viewRect(0.f, 0.f, 2790.f, 2790.f), m_bPaused(false), m_bGameOver(false)
{
    m_app.Create(sf::VideoMode(700.f, 700.f), "Snake");
    sf::View view(m_viewRect);
    m_app.SetView(view);
    m_eUserDirection = CURRENT;

    std::srand(time(NULL));
    m_food.randomizePosition();
}

void SnakeGame::reset()
{
    m_food.randomizePosition();
    m_snake.reset();
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

    m_snake.Move();
    m_food.Move();

    checkCollisions();
}

void SnakeGame::checkCollisions()
{
    if (m_snake.isSnakeCollision() || m_snake.isOutOfBounds(m_viewRect))
    {
        m_bGameOver = true;
    }

    if (m_snake.isCollision(m_food))
    {
        SnakeSection* section = new SnakeSection();
        section->SetPosition(m_food.GetPosition());
        m_snake.addSection(*section);

        m_food.randomizePosition();
    }
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
