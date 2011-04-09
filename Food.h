#ifndef FOOD_H
#define FOOD_H

#include "Common.h"
#include "GamePiece.h"
#include "Snake.h"

class Food : public GamePiece
{
    public:
        Food();
        virtual ~Food() { }
        virtual void handleCollision(Snake& snake, COLLISION_MAP_TYPE collisionMap[PIXEL_LINE_COUNT][PIXEL_LINE_COUNT]);
    protected:
    private:
};

#endif // FOOD_H
