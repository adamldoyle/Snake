#ifndef WALL_H
#define WALL_H

#include "Common.h"
#include "GamePiece.h"
#include "Snake.h"

class Wall : public GamePiece
{
    public:
        Wall();
        virtual ~Wall() { }
        virtual bool handleCollision(Snake& snake, COLLISION_MAP_TYPE collisionMap[PIXEL_LINE_COUNT][PIXEL_LINE_COUNT]);
    protected:
    private:
};

#endif // WALL_H
