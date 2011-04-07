#include "GamePiece.h"

GamePiece::GamePiece(int nDimension, sf::Color color, float fpXPosition, float fpYPosition, Direction eDirection, int nVelocity)
{
    m_nDimension = nDimension;
    m_color = color;
    m_visual = sf::Shape::Rectangle(0, 0, m_nDimension, m_nDimension, m_color);
    m_eDirection = eDirection;
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

bool GamePiece::isCollision(GamePiece& otherPiece)
{
    float fpLeft1 = GetPosition().x;
    float fpTop1 = GetPosition().y;
    float fpLeft2 = otherPiece.GetPosition().x;
    float fpTop2 = otherPiece.GetPosition().y;

    if (fpTop1 + m_nDimension < fpTop2)
        return false;
    if (fpTop2 + otherPiece.m_nDimension < fpTop1)
        return false;
    if (fpLeft1 + m_nDimension < fpLeft2)
        return false;
    if (fpLeft2 + otherPiece.m_nDimension < fpLeft1)
        return false;
    return true;
}

void GamePiece::randomizePosition()
{
    SetPosition((rand() % 56) * 50, (rand() % 56) * 50);
}
