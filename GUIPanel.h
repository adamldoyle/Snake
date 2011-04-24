#ifndef GUIPANEL_H
#define GUIPANEL_H

#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Snake.h"

class GUIPanel : public sf::Drawable
{
    public:
        GUIPanel(sf::FloatRect rect);
        virtual ~GUIPanel();
        void update(Snake& snake);
        void reset();
    protected:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
    private:
        sf::Shape m_background;
        sf::Shape m_border;

        int m_nPlayerScore;
        int m_nSnakeLength;

        static const int FOOD_BONUS = 200;
        static const int TIME_BONUS = 1;
        static const int PIECES_PER_TIME_BONUS = 5;
};

#endif // GUIPANEL_H
