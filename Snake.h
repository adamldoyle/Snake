#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
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
        bool isSnakeCollision();
        bool isOutOfBounds(sf::FloatRect viewRect);
        void stop();
    protected:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
    private:
        SnakeSection* m_head;
        SnakeSection* m_tail;
};

#endif // SNAKE_H
