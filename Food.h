#ifndef FOOD_H
#define FOOD_H

#include "Common.h"
#include "GamePiece.h"

class Food : public GamePiece
{
    public:
        Food(float fpXPosition, float fpYPosition);
        virtual ~Food() { }
    protected:
    private:
};

#endif // FOOD_H
