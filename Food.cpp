#include "Food.h"

Food::Food(float fpXPosition, float fpYPosition) : GamePiece(30, sf::Color::White, fpXPosition, fpYPosition, CURRENT, 0)
{
    m_visual.SetPosition(5.f, 5.f);
}
