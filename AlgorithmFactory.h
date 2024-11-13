/**
* Authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 7, 2023
* Purpose: Creates a factory class to store different pathfinding algorithms for use on the board
*/
#ifndef ALGORITHMFACTORY_H
#define ALGORITHMFACTORY_H

#include "Dijkstra.h"
#include "AStar.h"

/**
 * Factory for creating the pathfinding algorithm instance
 * @param type: Integer presenting algorithm type (0 for Disjkstra(default), 1 for AStar)
 * @param board: Pointer reference to current board
 * @return instance: An instance of the selected algorithm
*/
class AlgorithmFactory {
    public:
        Algorithm* createAlgorithmInstance(int type, Board* board) {
            Algorithm* instance;
            switch(type) {
                case 0:
                    instance = new Dijkstra(board);
                    break;
                case 1:
                    instance = new AStar(board);
                    break;
                default:
                    instance = new Dijkstra(board);
                    break;
            }
            return instance;
        }
};

#endif