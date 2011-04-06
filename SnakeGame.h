#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <SFML/Graphics.hpp>
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
        void resetEvents();
        void handleEvents();
        void updateGame();
        void checkCollisions();
        void displayGame();

        sf::RenderWindow m_app;
        Snake m_snake;
        Food m_food;
        Direction m_eUserDirection;
        sf::FloatRect m_viewRect;
};

#endif // SNAKE_GAME_H
