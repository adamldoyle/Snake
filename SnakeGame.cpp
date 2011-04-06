#include "SnakeGame.h"

const int FRAMES_PER_SECOND = 10;
const float SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
const int SLEEP_TICKS = 10;

SnakeGame::SnakeGame() : m_food(200, 200), m_viewRect(0.f, 0.f, 2790.f, 2790.f)
{
    m_app.Create(sf::VideoMode(700.f, 700.f), "Snake");
    sf::View view(m_viewRect);
    m_app.SetView(view);
    m_eUserDirection = CURRENT;
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

        updateGame();

        displayGame();
    }
}

void SnakeGame::resetEvents()
{
    m_eUserDirection = CURRENT;
}

void SnakeGame::handleEvents()
{
    sf::Event Event;
    while (m_app.GetEvent(Event))
    {
        if (Event.Type == sf::Event::Closed || (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)) {
            m_app.Close();
        }
    }

    if (m_app.IsOpened())
    {
        const sf::Input& Input = m_app.GetInput();
        if (Input.IsKeyDown(sf::Key::Up)) {
            m_eUserDirection = UP;
        } else if (Input.IsKeyDown(sf::Key::Down)) {
            m_eUserDirection = DOWN;
        } else if (Input.IsKeyDown(sf::Key::Left)) {
            m_eUserDirection = LEFT;
        } else if (Input.IsKeyDown(sf::Key::Right)) {
            m_eUserDirection = RIGHT;
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
    if (m_snake.isSnakeCollision())
    {
        m_snake.stop();
    }

    if (m_snake.isCollision(m_food))
    {
        SnakeSection* section = new SnakeSection();
        section->SetPosition(m_food.GetPosition());
        m_snake.addSection(*section);
    }

    if (m_snake.isOutOfBounds(m_viewRect))
    {
        m_snake.stop();
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
