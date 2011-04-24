#include "Wall.h"

Wall::Wall()  : GamePiece(50, sf::Color::White, sf::Vector2f(0.f, 0.f), PIECE_WALL, CURRENT, 0)
{
    m_visual.SetPosition(-5.f, -5.f);
}

bool Wall::handleCollision(Snake& snake, COLLISION_MAP_TYPE collisionMap[PIXEL_LINE_COUNT][PIXEL_LINE_COUNT])
{
    return true;
}
