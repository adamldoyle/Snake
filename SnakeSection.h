#ifndef SNAKE_SECTION_H
#define SNAKE_SECTION_H

#include "Common.h"
#include "GamePiece.h"

class SnakeSection;

class SnakeSection : public GamePiece
{
    friend class Snake;

    public:
        SnakeSection(float fpXPosition = 0.f, float fpYPosition = 0.f, COLLISION_MAP_TYPE pieceType = PIECE_SNAKE_BODY, Direction eDirection = CURRENT);
        virtual ~SnakeSection() { }
        void Move();
        virtual bool handleCollision(Snake& snake, COLLISION_MAP_TYPE collisionMap[PIXEL_LINE_COUNT][PIXEL_LINE_COUNT]) { return true; }
    protected:
        SnakeSection* m_nextSection;
        SnakeSection* m_pendingNextSection;
        void start();
    private:
        static const int VELOCITY = 50;
};

#endif // SNAKE_SECTION_H
