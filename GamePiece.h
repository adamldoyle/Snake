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

class GamePiece : public sf::Drawable
{
    public:
        GamePiece(int nDimension, sf::Color color, float fpXPosition, float fpYPosition, Direction eDirection = CURRENT, int nVelocity = 0);
        virtual ~GamePiece() { }
        virtual void Move();
        bool isCollision(GamePiece& otherPiece);
        void randomizePosition();
        void getPosition(int nPosition[2]);
    protected:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
        sf::Shape m_visual;
        sf::Color m_color;
        Direction m_eDirection;
        int m_nDimension;
        int m_nVelocity;
    private:

};

#endif // GAME_PIECE_H
