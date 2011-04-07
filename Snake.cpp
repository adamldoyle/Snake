#include "Snake.h"

Snake::Snake() : sf::Drawable()
{
    m_head = m_tail = new SnakeSection(0.f, 0.f, RIGHT);
    m_head->start();
}

Snake::~Snake()
{
    SnakeSection *temp, *curr = m_head;
    while (curr != NULL)
    {
        temp = curr;
        curr = curr->m_nextSection;
        free(temp);
    }
}

void Snake::reset()
{
    SnakeSection *temp, *curr = m_head->m_nextSection;
    while (curr != NULL)
    {
        temp = curr;
        curr = curr->m_nextSection;
        delete temp;
    }
    m_head->m_nextSection = NULL;
    m_tail = m_head;
    m_head->SetPosition(0.f, 0.f);
    m_head->m_eDirection = RIGHT;
}

void Snake::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    SnakeSection* curr = m_head;
    while (curr != NULL)
    {
        target.Draw(*curr);
        curr = curr->m_nextSection;
    }
}

void Snake::Move()
{
    m_head->Move();
}

void Snake::ChangeDirection(Direction& eDirection)
{
    switch (eDirection)
    {
        case UP:
        case DOWN:
            if (m_head->m_eDirection == RIGHT || m_head->m_eDirection == LEFT)
                m_head->m_eDirection = eDirection;
            break;
        case LEFT:
        case RIGHT:
            if (m_head->m_eDirection == UP || m_head->m_eDirection == DOWN)
                m_head->m_eDirection = eDirection;
            break;
        default:
            break;
    }
}

void Snake::addSection(SnakeSection& section)
{
    m_tail->m_nextSection = &section;
    m_tail = &section;
}

bool Snake::isCollision(GamePiece& otherPiece)
{
    return m_head->isCollision(otherPiece);
}

bool Snake::isSnakeCollision()
{
    SnakeSection* curr = m_head->m_nextSection;
    while (curr != NULL)
    {
        if (curr->m_nVelocity > 0 && isCollision(*curr))
        {
            return true;
        }
        curr = curr->m_nextSection;
    }
    return false;
}

bool Snake::isOutOfBounds(sf::FloatRect viewRect)
{
    return (m_head->GetPosition().x < viewRect.Left || m_head->GetPosition().y < viewRect.Top
        || m_head->GetPosition().x + m_head->m_nDimension > viewRect.Left + viewRect.Width || m_head->GetPosition().y + m_head->m_nDimension > viewRect.Top + viewRect.Height);
}
