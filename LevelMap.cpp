/**
* Authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 28, 2023
* Purpose: To act as a 2D map and contains every information about it.
*/
#include "LevelMap.h"

/**
* Set the map when we need to have custom map.
* @param map: it is a matrix of Blocks which represent the 2D map information.
*/
void LevelMap::setMap(std::vector<std::vector<Block>> map)
{
   this->map = map;
}

/**
* Return the map information.
* @return map: it is a matrix of Blocks which represent the 2D map information.
*/
std::vector<std::vector<Block>> LevelMap::getMap() {
   return map;
}

/**
* Return the selected positioned node pointer reference.
* @return block: it is a block pointer related to a selected position.
*/
Block* LevelMap::getNode(int row, int col) {
   return &map[row][col];
}

/**
* Set which floor this map represent.
* @param floor: it indicate which floor plan for the building this map is represent.
*/
void LevelMap::setFloor(int level){
   floor = level;
}

/**
* Return the floor level this map represent.
* @return floor: it indicate which floor plan for the building this map is represent.
*/
int LevelMap::getFloor(){
   return floor;
}

/**
* add the entrance node to the floor plan map.
* @param entrance: it indicate a pointer of which node is the entrance node in map.
*/
void LevelMap::addEntrance(Block* entrance){
   entrances.push_back(entrance);
}

/**
* add the exit node to the floor plan map.
* @param exit: it indicate a pointer of which node is the exit node in map.
*/
void LevelMap::addExit(Block* exit){
   exits.push_back(exit);
}

/**
* set the start point node to the 2D map.
* @param startPoint: it indicate a pointer of which node is the start point node in map.
*/
void LevelMap::setStartPoint(Block* startPoint)
{
   this->startPoint = startPoint;
}

/**
* set the target point node to the 2D map.
* @param targetPoint: it indicate a pointer of which node is the target point node in map.
*/
void LevelMap::setTargetPoint(Block* targetPoint)
{
   this->targetPoint = targetPoint;
}

/**
* set the start point node to the 2D map based on its row and column.
* @param row: it indicate which row the start point is in map.
* @param col: it indicate which column the start point is in map.
*/
void LevelMap::setStartPoint(int row, int col)
{
   startPoint = &map[row][col];
}

/**
* set the target point node to the 2D map based on its row and column.
* @param row: it indicate which row the target point is in map.
* @param col: it indicate which column the target point is in map.
*/
void LevelMap::setTargetPoint(int row, int col)
{
   targetPoint = &map[row][col];
}

/**
* get the start point node to the 2D map.
* @return startPoint: it indicate a pointer of which node is the start point node in map.
*/
Block* LevelMap::getStartPoint()
{
   return startPoint;
}

/**
* get the target point node to the 2D map.
* @return target: it indicate a pointer of which node is the target point node in map.
*/
Block* LevelMap::getTargetPoint()
{
   return targetPoint;
}

/**
* find the node pointer reference on the 2D map based on its row and column.
* @param row: it indicate which row the node is in map.
* @param col: it indicate which column the node is in map.
* @return block: it is the pointer reference of selected node.
*/
Block* LevelMap::findBlockInMap(int row, int col)
{
   return &map[row][col];
}

/**
* find the walls information on the map.
* @return walls: it is a list of walls location on map.
*/
std::vector<std::pair<int, int>> LevelMap::getWallsInfo() {
   std::vector<std::pair<int, int>> walls;
   for(int i = 0; i < map.size(); i++) {
      for(int j = 0; j < map[i].size(); j++) {
         Block node = map[i][j];
         if(node.getType() == 5) {
            std::pair<int, int> wall(i, j);
            walls.push_back(wall);
         }
      }
   }
   return walls;
}

/**
* It reset the map's blocks settings after run the algorithm.
*/
void LevelMap::resetMapBlocks() {  
   for(int row = 0; row < 20; row++) {
      for(int col = 0; col < 52; col++) {
            Block* currNode = &map[row][col];
            currNode->setInQueue(false);
            currNode->setMinDistance(10000);
            currNode->setWeight(1);
            currNode->setPrevBlock(nullptr);
            currNode->setVisit(false);
      }
   }
}