#include "GUIPanel.h"
#include <stdio.h>

GUIPanel::GUIPanel(sf::FloatRect rect) : sf::Drawable(), m_nPlayerScore(0), m_nSnakeLength(1)
{
    m_background = sf::Shape::Rectangle(rect, sf::Color::Black);
    m_border = sf::Shape::Rectangle(sf::FloatRect(-20.f, 0.f, 20.f, rect.Height), sf::Color::White);
}

GUIPanel::~GUIPanel()
{
    //dtor
}

void GUIPanel::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    target.Draw(m_background);
    target.Draw(m_border);

    char buffer[15];
    sprintf(buffer, "%d", m_nPlayerScore);

    sf::Text temp = sf::Text(buffer);
    target.Draw(temp);
}

void GUIPanel::update(Snake& snake)
{
    if (snake.getSize() > m_nSnakeLength)
    {
        m_nPlayerScore += FOOD_BONUS;
    }
    m_nSnakeLength = snake.getSize();

    int bonus = (m_nSnakeLength / PIECES_PER_TIME_BONUS) + 1;
    m_nPlayerScore += (bonus * TIME_BONUS);
}
