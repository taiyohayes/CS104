#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "solver.h"

using namespace std;

// To be completed
Solver::Solver(const Board& b, Heuristic *heur)
{
    b_ = b;
    heur_ = heur;
    expansions_ = 0;
    solution_.clear();
}

// To be completed
Solver::~Solver()
{
}

// To be completed
bool Solver::run()
{
    MoveHeap open;
    MoveSet closed;
    Board* currentBoard = new Board(b_);
    Move* parent = new Move(currentBoard); 
    open.push(parent);
    closed.insert(parent);
    expansions_++;
    Move* lastMove = NULL;
    bool solve = false;
    while(!(open.empty()))
    {
        if (currentBoard->solved())
        {
            solve = true;
            break;
        }
        parent = open.top();
        lastMove = parent;
        open.pop();
        currentBoard = parent->b;
        Board::MovePairList pMoves = currentBoard->potentialMoves();
        for (Board::MovePairList::iterator it = pMoves.begin(); it != pMoves.end(); ++it)
        {
            Board* newBoard = new Board(*currentBoard);
            if (newBoard->move(it->first, it->second) == true)
            {
                Move* newMove = new Move(*it, newBoard, parent);
                newMove->score(heur_);
                if (closed.find(newMove) == closed.end())
                {
                    open.push(newMove);
                    closed.insert(newMove);
                    expansions_++;
                }
            }
        }
    }
    delete parent;
    delete currentBoard;
    if (solve == true)
    {
        if (lastMove == NULL)
        {
            return true;
        }
        while (lastMove != NULL)
        { 
            solution_.push_back(lastMove->m);
            lastMove = lastMove->prev;
        }
        solution_.pop_back();
        return true;
    }
    solution_.clear();
    return false;
}

// To be completed
Board::MovePairList Solver::solution() const
{
    Board::MovePairList revSol;
    for (Board::MovePairList::const_iterator it = solution_.end(); it-- != solution_.begin();)
    {
        revSol.push_back(*it);
    }
    return revSol;
}

// Complete
size_t Solver::numExpansions() const
{
    return expansions_;
}
