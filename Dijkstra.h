/**
 * @authors Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
 * @brief Class to calculate the shortest path between start and destination locations using Dijkstra's Algorithm.
 * Date: November 28, 2023
*/
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#pragma once
#include <queue>
#include <unistd.h>
#include <vector>
#include "Algorithm.h"
#include "Block.h"

struct dijkstracompare {
   bool operator()(Block* const& a,Block* const& b)
   {
       return a->getMinDistance() > b->getMinDistance();
   }
};

class Dijkstra : public Algorithm
{
    public:
        Dijkstra(Board* board) { 
            currentBoard = board;
        }
        std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> runAlgorithm();
    private:
        int distance = 0;
        std::vector<Block*> visited;
        std::priority_queue<Block*, std::vector<Block*>, dijkstracompare> unvisited;
        void addNeighboursToUnvisited(Block* node);
        void reorderPriorityQueue(Block* node);
        std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> findShortestPathOnMap(Block* startLoc, Block* targetLoc);
        std::vector<Block*> sortByWeight(std::vector<Block*> connections);
        void calculateShortestDistance(Block* currNode, std::vector<Block*> connections);
};
#endif
