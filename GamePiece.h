#ifndef GAME_PIECE_H
#define GAME_PIECE_H

#include <SFML/Graphics.hpp>
#include "Common.h"

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    CURRENT
};

class GamePiece;
class Snake;

class GamePiece : public sf::Drawable
{
    public:
        GamePiece(int nDimension, sf::Color color, sf::Vector2f position, COLLISION_MAP_TYPE pieceType = PIECE_NONE, Direction eDirection = CURRENT, int nVelocity = 0);
        virtual ~GamePiece() { }
        virtual void Move();
        void randomizePosition();
        sf::Vector2i getPosition();
        COLLISION_MAP_TYPE getPieceType() { return m_pieceType; }
        virtual bool handleCollision(Snake& snake, COLLISION_MAP_TYPE collisionMap[PIXEL_LINE_COUNT][PIXEL_LINE_COUNT]) = 0;
        void place(COLLISION_MAP_TYPE collisionMap[PIXEL_LINE_COUNT][PIXEL_LINE_COUNT]);
    protected:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
        sf::Shape m_visual;
        sf::Color m_color;
        Direction m_eDirection;
        int m_nDimension;
        int m_nVelocity;
        COLLISION_MAP_TYPE m_pieceType;
    private:

};

#endif // GAME_PIECE_H
