/**
* Authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 7, 2023
* Purpose: Class to calculate the shortest path between start and destination locations using AStar Algorithm.
*/

#include "AStar.h"
#include "Interface.h"
using namespace std;

/**
* Finds the shortest path(s) from starting to destination locations based on map type.
* @return result:The shortest path
*/
pair<vector<pair<int, int>>, vector<pair<int, int>>> AStar::runAlgorithm() {
   vector<vector<Block*>> shortestPath;
   vector<Block*> pathInstance;
   //get start and end points
   Block* startBlock = currentBoard->getMap()->getStartPoint();
   Block* targetBlock = currentBoard->getMap()->getTargetPoint();
   pair<vector<pair<int, int>>, vector<pair<int, int>>> result = findShortestPathOnMap(startBlock, targetBlock);
   return result;
}

/**
 * Creates a vector containing a list of unvisited blocks to be visited.
 * @param node: The current block.
 * @param targetLoc: The target block.
*/
void AStar::addNeighboursToUnvisited(Block* node, Block* targetLoc) {
    vector<Block*> neighbours = node->getNeighbour();
    int parent_g_cost = node->getGCost();
    for(Block* neighbour: neighbours){
        // if neighbour is not wall
        if(!neighbour->visited() && neighbour->getType() != 5) {
            int row = neighbour->getRow();
            int col = neighbour->getColumn();
            bool updated = neighbour->updateGCost(row, col, parent_g_cost);
            neighbour->calculateHCost(targetLoc->getRow(), targetLoc->getColumn());
            if(updated) neighbour->setPrevBlock(node);
            if(!neighbour->isInQueue()) {             
                neighbour->setInQueue(true);
                unvisited.push(neighbour);
            } else {
                // if this neighbour node is already in priority queue, then we change the min dist and update order
                reorderPriorityQueue(node);
            }   
        }
    }
}

/**
 * Function to reorder the priority queue if the block is already in the queue.
 * @param node: The block to be pushed to the priority queue.
*/
void AStar::reorderPriorityQueue(Block* node) {
    vector<Block*> temp_array;
    Block* curr = unvisited.top();
    bool sameCol = node->getColumn() == curr->getColumn();
    bool sameRow = node->getRow() == curr->getRow();
    bool sameNode = sameCol && sameRow;
    while(!sameNode) {
        if(!unvisited.empty()){
            temp_array.push_back(curr);
            unvisited.pop();
            curr = unvisited.top();
        } else {
            break;
        }
    }
    unvisited.pop();
    unvisited.push(curr);
    for(Block* b: temp_array) {
        unvisited.push(b);
    }
}
/**
* Finds the shortest distance between the start and target locations using AStar Algorithm.
* @param startLoc: The starting block.
* @param targetLoc: The destination block.
* @return result: The shortest path.
*/
pair<vector<pair<int, int>>, vector<pair<int, int>>> AStar::findShortestPathOnMap(Block* startLoc, Block* targetLoc) {
    vector<pair<int, int>> visitedNode;
    vector<pair<int, int>> shortestPathNodes;
    unvisited.push(startLoc);
    Block* curr = unvisited.top();
    curr->calculateHCost(targetLoc->getRow(), targetLoc->getColumn());
    curr->setGCost(0);
    while(!unvisited.empty()){
        if(curr->visited()){
            unvisited.pop();
            continue;
        }   
        unvisited.pop();
        curr->setVisit(true);
        // add its neighbours to priority queue
        addNeighboursToUnvisited(curr, targetLoc);
        int x = curr->getRow();
        int y = curr->getColumn();
        pair<int, int> node(x, y);
        visitedNode.push_back(node);
        if(curr == targetLoc) {
            break;
        }
        curr = unvisited.top();
    }
    if(curr == targetLoc) {
        int row = curr->getRow();
        int col = curr->getColumn();
        pair<int, int> pathNode(row, col);
        shortestPathNodes.insert(shortestPathNodes.begin(), pathNode);
        while(curr->getPrevBlock()) {
            int prevRow = curr->getPrevBlock()->getRow();
            int prevCol = curr->getPrevBlock()->getColumn();
            pathNode = make_pair(prevRow, prevCol);
            shortestPathNodes.insert(shortestPathNodes.begin(), pathNode);
            curr = curr->getPrevBlock();
        }
    }
    pair<vector<pair<int, int>>, vector<pair<int, int>>> result(visitedNode, shortestPathNodes);
    return result;
}

/**
* Method to sort the connection blocks from greatest to least in weight.
* @param connections: the blocks to be sorted.
* @return sortedConnections: the blocks sorted by weight.
*/
vector<Block*> AStar::sortByWeight(vector<Block*> connections) {
   vector<Block*> sortedConnections;
   int numConnections = connections.size();
   int numSortedConnections = 0;

   //If there are no connections there is nothing to sort and return empty set of connections.
   if(numConnections == 0) {
       return connections;
   }

   //Sorts connection vector from highest to lowest weight and returns sorted vector.
   for(int i = 0; i < numConnections; i++) {
       Block* tempBlock = connections.at(numConnections-1);
       connections.pop_back();
       if(numSortedConnections == 0) {
           sortedConnections.push_back(tempBlock);
           numSortedConnections++;
       }
       else {
           for(int j = numSortedConnections; j < numConnections; j++) {
               if(tempBlock->getWeight() >= sortedConnections.at(j)->getWeight()) {
                   vector<Block*>::iterator iter = sortedConnections.begin() + i;
                   sortedConnections.insert(iter, tempBlock);
                   numSortedConnections++;
               }
           }
       }
   }
   return sortedConnections;
}

/**
* Method to calculate the shortest distance between the starting node and each node in the grid.
* @param currBlock: the node to compute the shortest distance from.
* @param connections: the set of adjacent nodes.
*/

void AStar::calculateShortestDistance(Block* currBlock, vector<Block*> connections)
{
   for(int i = 0; i < connections.size(); i++) {
       //Get the block's connections and calculate their distance from the starting node.
       Block* nextBlock = connections.at(i);
       if(nextBlock->visited()) continue;
       int dist = nextBlock->getWeight() + currBlock->getMinDistance();

       //If the distance found to the block is shorter than the previously stored distance set the smaller distance to the min distance.
       if (dist < nextBlock->getMinDistance()) {
           nextBlock->setMinDistance(dist);
       }
       calculateShortestDistance(nextBlock, sortByWeight(currBlock->getNeighbour()));
   }
}