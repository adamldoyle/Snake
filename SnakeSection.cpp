#include "SnakeSection.h"

SnakeSection::SnakeSection(float fpXPosition, float fpYPosition, Direction eDirection) : GamePiece(40, sf::Color::White, fpXPosition, fpYPosition, eDirection, 0.f), m_nextSection(NULL)
{

}

void SnakeSection::Move()
{
    // New piece should start moving on the next turn
    if (m_nextSection != NULL && isCollision(*m_nextSection))
    {
        m_nextSection->start();
        m_nextSection->m_eDirection = CURRENT;
    }

    GamePiece::Move();

    // After this movement, following piece should move in current pieces direction
    if (m_nextSection != NULL)
    {
        m_nextSection->Move();
        m_nextSection->m_eDirection = m_eDirection;
    }
}

void SnakeSection::start()
{
    m_nVelocity = VELOCITY;
}
