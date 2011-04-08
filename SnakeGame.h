#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Snake.h"
#include "Food.h"

class SnakeGame
{
    public:
        SnakeGame();
        virtual ~SnakeGame() { }

        void run();
    protected:
    private:
        void reset();
        void resetEvents();
        void handleEvents();
        void updateGame();
        void checkCollisions();
        bool isCollision(COLLISION_MAP_TYPE collisionValue, COLLISION_MAP_TYPE checkAgainst);
        void displayGame();
        void placeFood();
        void placeSnake();
        void placeWalls();

        sf::RenderWindow m_app;
        Snake m_snake;
        Food m_food;
        Direction m_eUserDirection;
        sf::FloatRect m_viewRect;
        bool m_bPaused;
        bool m_bGameOver;


        COLLISION_MAP_TYPE m_collisionMap[PIXEL_LINE_COUNT][PIXEL_LINE_COUNT];
};

#endif // SNAKE_GAME_H
