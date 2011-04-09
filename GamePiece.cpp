#include "GamePiece.h"

GamePiece::GamePiece(int nDimension, sf::Color color, float fpXPosition, float fpYPosition, COLLISION_MAP_TYPE pieceType, Direction eDirection, int nVelocity)
{
    m_nDimension = nDimension;
    m_color = color;
    m_visual = sf::Shape::Rectangle(0, 0, m_nDimension, m_nDimension, m_color);
    m_eDirection = eDirection;
    m_pieceType = pieceType;
    m_nVelocity = nVelocity;
    SetPosition(fpXPosition, fpYPosition);
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

void GamePiece::getPosition(int nPosition[2])
{
    nPosition[0] = (int)GetPosition().x / PIXEL_DIMENSION;
    nPosition[1] = (int)GetPosition().y / PIXEL_DIMENSION;
}

void GamePiece::place(COLLISION_MAP_TYPE collisionMap[PIXEL_LINE_COUNT][PIXEL_LINE_COUNT])
{
    int nPosition[2];
    while (1)
    {
        randomizePosition();
        getPosition(nPosition);
        if (collisionMap[nPosition[0]][nPosition[1]] == PIECE_NONE)
        {
            collisionMap[nPosition[0]][nPosition[1]] = m_pieceType;
            break;
        }
    }
}
