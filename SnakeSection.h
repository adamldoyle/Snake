#ifndef SNAKE_SECTION_H
#define SNAKE_SECTION_H

#include "GamePiece.h"

class SnakeSection;

class SnakeSection : public GamePiece
{
    friend class Snake;

    public:
        SnakeSection(float fpXPosition = 0.f, float fpYPosition = 0.f, Direction eDirection = CURRENT);
        virtual ~SnakeSection() { }
        void Move();
    protected:
        SnakeSection* m_nextSection;
        void start();
    private:
        static const int VELOCITY = 50;
};

#endif // SNAKE_SECTION_H
