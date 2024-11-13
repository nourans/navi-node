/**
* Authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 7, 2023
* Purpose: Creates a centralized class to store different pathfinding algorithms.
*/

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include "Board.h"

/**
* Abstract algorithm class and connects it to current board.
*/
class Algorithm
{
   protected:
       Board* currentBoard;
   public:
       virtual std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> runAlgorithm() = 0;
};

#endif