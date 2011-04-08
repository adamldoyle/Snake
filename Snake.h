#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include "Common.h"
#include "SnakeSection.h"

class Snake : public sf::Drawable
{
    public:
        Snake();
        virtual ~Snake();
        void Move();
        void ChangeDirection(Direction& eDirection);
        void addSection(SnakeSection& section);
        bool isCollision(GamePiece& otherPiece);
        bool isOutOfBounds(sf::FloatRect viewRect);
        void reset();
        void getHeadPosition(int nPosition[2]);
        void getTailPosition(int nPosition[2]);
        int getSize();
    protected:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
    private:
        SnakeSection* m_head;
        SnakeSection* m_tail;
        int m_nSize;
};

#endif // SNAKE_H
