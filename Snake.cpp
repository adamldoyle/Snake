#include "Snake.h"

Snake::Snake() : sf::Drawable(), m_nSize(1)
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
    if (m_tail->m_pendingNextSection != NULL && m_tail->isCollision(*(m_tail->m_pendingNextSection)))
    {
        m_tail->m_nextSection = m_tail->m_pendingNextSection;
        m_tail->m_pendingNextSection = NULL;
        m_tail = m_tail->m_nextSection;
        m_tail->start();
        m_nSize++;
    }

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
    SnakeSection* curr = m_tail;
    while (curr->m_pendingNextSection != NULL)
    {
        curr = curr->m_pendingNextSection;
    }
    curr->m_pendingNextSection = &section;
}

bool Snake::isCollision(GamePiece& otherPiece)
{
    return m_head->isCollision(otherPiece);
}

bool Snake::isOutOfBounds(sf::FloatRect viewRect)
{
    return (m_head->GetPosition().x < viewRect.Left || m_head->GetPosition().y < viewRect.Top
        || m_head->GetPosition().x + m_head->m_nDimension > viewRect.Left + viewRect.Width || m_head->GetPosition().y + m_head->m_nDimension > viewRect.Top + viewRect.Height);
}

void Snake::getHeadPosition(int nPosition[2])
{
    m_head->getPosition(nPosition);
}

void Snake::getTailPosition(int nPosition[2])
{
    m_tail->getPosition(nPosition);
}

int Snake::getSize()
{
    return m_nSize;
}
