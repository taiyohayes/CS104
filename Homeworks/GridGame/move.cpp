#include "move.h"

// Complete
Move::Move(Board* board)
{
    m.first = Vehicle::INVALID_ID;
    m.second = 0;
    b = board;
    g = 0;
    h = 0;
    prev = NULL;
}

// To be completed
Move::Move(const Board::MovePair& move, Board* b,  Move *parent)
{
    m.first = move.first;
    m.second = move.second;
    this->b = b;
    prev = parent;
    g = (prev->g) + 1;
    h = 0;
}

// To be completed
Move::~Move()
{

}

// To be completed
bool Move::operator<(const Move& rhs) const
{
    int f = g + h;
    int rF = rhs.g + rhs.h;
    if (f < rF)
    {
        return true;
    }
    return false;
}

// To be completed
void Move::score(Heuristic *heur) 
{
    h = heur->compute(*b);
}
