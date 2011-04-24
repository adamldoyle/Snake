#include "GamePiece.h"

#define COLLISION_MAP_POINT(vector) collisionMap[vector.x][vector.y]

GamePiece::GamePiece(int nDimension, sf::Color color, sf::Vector2f position, COLLISION_MAP_TYPE pieceType, Direction eDirection, int nVelocity)
{
    m_nDimension = nDimension;
    m_color = color;
    m_visual = sf::Shape::Rectangle(0, 0, m_nDimension, m_nDimension, m_color);
    m_eDirection = eDirection;
    m_pieceType = pieceType;
    m_nVelocity = nVelocity;
    SetPosition(position);
}

void GamePiece::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    target.Draw(m_visual);
}

void GamePiece::Move()
{
    int nXDirection = 0, nYDirection = 0;
    switch (m_eDirection)
    {
        case UP:
            nYDirection = -1;
            break;
        case DOWN:
            nYDirection = 1;
            break;
        case LEFT:
            nXDirection = -1;
            break;
        case RIGHT:
            nXDirection = 1;
            break;
        default:
            break;
    }

    sf::Drawable::Move(nXDirection * m_nVelocity, nYDirection * m_nVelocity);
}

void GamePiece::randomizePosition()
{
    SetPosition((rand() % PIXEL_LINE_COUNT) * PIXEL_DIMENSION, (rand() % PIXEL_LINE_COUNT) * PIXEL_DIMENSION);
}

sf::Vector2i GamePiece::getPosition()
{
    int x = (int)GetPosition().x / PIXEL_DIMENSION;
    int y = (int)GetPosition().y / PIXEL_DIMENSION;
    return sf::Vector2i(x, y);
}

void GamePiece::place(COLLISION_MAP_TYPE collisionMap[PIXEL_LINE_COUNT][PIXEL_LINE_COUNT])
{
    sf::Vector2i position;
    while (1)
    {
        randomizePosition();
        position = getPosition();
        if (COLLISION_MAP_POINT(position) == PIECE_NONE)
        {
            COLLISION_MAP_POINT(position) = m_pieceType;
            break;
        }
    }
}
