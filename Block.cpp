/**
* Authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 7, 2023
* Purpose: To initialize a single point in a grid as a location on the map.
*/

#include "Block.h"
using namespace std;

/**
* This method sets the weight of the block.
* @param weight: the amount of energy required to traverse to the block
*/
void Block::setWeight(int blockWeight) {
   weight = blockWeight;
}

/**
* This method sets the type of the block.
* @param type: The type of block (classroom, path, wall, etc.)
*/
void Block::setType(int blockType) {
   type = blockType;
}

/**
* Sets an adjacent block as a neighbouring block.
* @param n: The adjacent block.
*/
void Block::setNeighbour(Block* n) {
   neighbours.push_back(n);
}

/**
* Sets whether the block has been traversed.
* @param visited: true is yes, otherwise false.
*/
void Block::setVisit(bool visited) {
   visit = visited;
}

/**
 * Sets the block to being in the queue
 * @param inQueue: true if block is in queue otherwise false.
*/
void Block::setInQueue(bool inQueue){
   this->inQueue = inQueue;
}

/**
 * Returns whether the block is in the queue
 * @return inQueue: true if in queue otherwise false.
*/
bool Block::isInQueue() {
   return inQueue;
}

/**
* Sets the minimum distance between the starting block and this block.
* @param blockDist: the distance from the starting block.
*/
void Block::setMinDistance(int blockDist) {
   dist = blockDist;
}


/**
* Returns the weight of the block.
* @return weight: The weight of the block.
*/
int Block::getWeight() {
   return weight;
}

/**
* Returns the type of the block.
* @return type: the block's type.
*/
int Block::getType() {
   return type;
}

/**
* Returns the position of the block in terms of its row in the grid.
* @return row: the vertical position of the block.
*/
int Block::getRow() {
   return row;
}

/**
* Returns the position of the block in terms of its column.
* @return column: the horizontal position of the block.
*/
int Block::getColumn() {
   return column;
}

/**
* Returns a vector of the block's adjacent blocks.
* @return neighbours: a vector of adjacent blocks.
*/
vector<Block*> Block::getNeighbour() {
   return neighbours;
}

/**
* Returns whether the block has been traversed.
* @return visit: true if yes, otherwise false.
*/
bool Block::visited() {
   return visit;
}

/**
* Returns the distance from the starting node.
* @return dist: the distance from the starting node.
*/
int Block::getMinDistance() {
   return dist;
}

/**
 * Sets the previous block.
 * @param block: The previous block.
*/
void Block::setPrevBlock(Block* block) {
   prevBlock = block;
}

/**
 * Gets the previous block.
 * @return prevBlock: the previous block.
*/
Block* Block::getPrevBlock(){
   return prevBlock;
}

/**
 * method for A star algorithm
 * distance from start node
 * @param startRow: The start block row.
 * @param startCol: The start block column.
 * @param parent_node_g_cost: parent node's G cost
 * @return true or false: check if the G cost was updated or not
 * 
*/
bool Block::updateGCost(int startRow, int startCol, int parent_node_g_cost){
   if(g_cost > abs(startRow - row) + abs(startCol - column) + parent_node_g_cost){
      g_cost = abs(startRow - row) + abs(startCol - column) + parent_node_g_cost;
      return true;
   }
   return false;
}

/**
 * method for A star algorithm
 * @param cost: The G cost.
 * 
*/
void Block::setGCost(int cost) {
   g_cost = cost;
}

/**
 * method for A star algorithm
 * distance from end node
 * @param targetRow: target node row.
 * @param targetCol: target node column.
 * 
*/
void Block::calculateHCost(int targetRow, int targetCol){
   h_cost = abs(targetRow - row) + abs(targetCol - column);
}

/**
 * Get the G cost of node
 * @return g_cost: G cost of node.
 * 
*/
int Block::getGCost(){
   return g_cost;
}

/**
 * Get the H cost of node
 * @return h_cost: H cost of node.
 * 
*/
int Block::getHCost(){
   return h_cost;
}
