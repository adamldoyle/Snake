#include "Food.h"

Food::Food() : GamePiece(30, sf::Color::White, 0.f, 0.f, PIECE_FOOD, CURRENT, 0)
{
    m_visual.SetPosition(5.f, 5.f);
}

bool Food::handleCollision(Snake& snake, COLLISION_MAP_TYPE collisionMap[PIXEL_LINE_COUNT][PIXEL_LINE_COUNT])
{
    int nPosition[2];
    getPosition(nPosition);
    SnakeSection* section = new SnakeSection(GetPosition().x, GetPosition().y);
    snake.addSection(*section);

    collisionMap[nPosition[0]][nPosition[1]] ^= m_pieceType;

    place(collisionMap);

    return false;
}
