/**
* Authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 7, 2023
* Purpose: Class to calculate the shortest path between start and destination locations using AStar Algorithm.
*/
#ifndef ASTAR_H
#define ASTAR_H

#pragma once
#include <queue>
#include <unistd.h>
#include <vector>
#include "Algorithm.h"
#include "Block.h"

/**
* Custom comparison definition to compare the cost of paths
* @param a: A path of nodes
* @param b: A path of nodes to compare 
* @return a_f_cost > b_f_cost: A comparison for finding lower costs
*/
struct astarcompare {
    bool operator()(Block* const& a,Block* const& b)
    {
        // if f_cost = g_cost + h_cost is equal, then we should put smaller h_cost node
        int a_f_cost = a->getGCost() + a->getHCost();
        int b_f_cost = b->getGCost() + b->getHCost();
        if(a_f_cost == b_f_cost){
            return a->getHCost() > b->getHCost();
        }
        return a_f_cost > b_f_cost;
    }
};
/**
* AStar pathfinding algorithm definition 
* @param board: Pointer reference to current board
*/
class AStar : public Algorithm
{
   public:
       AStar(Board* board) {
           currentBoard = board;
       }
       std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> runAlgorithm();
   private:
       std::vector<Block*> visited;
       std::priority_queue<Block*, std::vector<Block*>, astarcompare> unvisited;
       void reorderPriorityQueue(Block* node);
       void addNeighboursToUnvisited(Block* node, Block* targetLoc);
       int distance = 0;
       std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> findShortestPathOnMap(Block* startLoc, Block* targetLoc);
       std::vector<Block*> sortByWeight(std::vector<Block*> connections);
       void calculateShortestDistance(Block* currNode, std::vector<Block*> connections);
};
#endif