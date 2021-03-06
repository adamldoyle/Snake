#include "SnakeSection.h"

SnakeSection::SnakeSection(sf::Vector2f(position), COLLISION_MAP_TYPE pieceType, Direction eDirection) : GamePiece(40, sf::Color::Green, position, pieceType, eDirection, 0.f), m_nextSection(NULL), m_pendingNextSection(NULL)
{

}

void SnakeSection::Move()
{
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
