/**
* Authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 7, 2023
* Purpose: To create an object class to store the individual map blocks.
*/

#ifndef BLOCK_H
#define BLOCK_H

#include <limits>
#include <vector>
#include <stdlib.h>

/**
* Class storing information pertaining to the grid positions.
*/
class Block {
    public:
        /**
            * Constructor to create a block and set default values.
            * @param type: 1 for traversable, 2 for elevators and stairs, 3 for classrooms_entrance, 4 for entrances, 5 for walls.
            * @param weight: Default value of 1. The higher the weight the more energy required to get to that block
            * @param x: the row of the block.
            * @param y: the column of the block.
            */
        Block() {}
        Block(int x, int y, int blockType=1, int blockWeight=1){
            type = blockType;
            weight = blockWeight;
            row = x;
            column = y;
            visit = false;
            dist = 100000;
            prevBlock = nullptr;
            inQueue = false;
            g_cost = 100000;
            h_cost = 100000;
        };
        void setWeight(int weight);
        void setType(int type);
        void setNeighbour(Block* n);
        void setVisit(bool visited);
        void setInQueue(bool inQueue);
        void setMinDistance(int dist);
        void setPrevBlock(Block* block);
        Block* getPrevBlock();
        int getWeight();
        int getType();
        int getRow();
        int getColumn();
        std::vector<Block*> getNeighbour();
        bool visited();
        bool isInQueue();
        int getMinDistance();
        bool updateGCost(int startRow, int startCol, int parent_node_g_cost);
        void calculateHCost(int targetRow, int targetCol);
        int getGCost();
        int getHCost();
        void setGCost(int cost);
    private:
        int type;
        int weight;
        int row;
        int column;
        std::vector<Block*> neighbours;
        bool visit;
        int dist;
        bool inQueue;
        Block* prevBlock;
        int g_cost;
        int h_cost;
};
#endif