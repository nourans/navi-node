/**
* Authors @authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 7, 2023
* Purpose @brief: To create an object class to store the board.
*/

#include "Board.h"

void Board::initCampusMap() {
   campusMap = LevelMap(1);
}

/** 
* This will get the map type.
* @brief: This will return the map type
* @returns: maptype 
*/
int Board::getMapType(){
   // 0 - classic map
   // 1 - campus map
   return mapType;
}

/** 
* This will get the main map
* @brief: This will get the main map or the campus map.
* @returns: classic or main map
*/
LevelMap* Board::getMap() {
   if(mapType == 0) {
       return &classicMap;
   } else {
       return &campusMap;
   }
};

/**
* This switches the map type from the campus map to the classic map.
* @brief: This switches the map type.
*/
void Board::switchMap(int type) {
   /*
    * type: 0 - classic
    *       1 - campus map
    */
   switch(type) {
      case 0:
         setBoardMapType(0);             
         classicMap = LevelMap();
         break;
      case 1:
         setBoardMapType(1);
         campusMap = LevelMap(1);
   }
}

/**
* This will set the board type.
* @brief: this will set the map of the board.
*/
void Board::setBoardMapType(int num) {
   mapType = num;
}

/**
* This will set the starting building map
* @brief: this will set the starting map
*/
void Board::setStartBuildingMap(std::vector<LevelMap> buildingMap) {
   startBuildingMap = buildingMap;
}

/**
* This will set the target building 
* @brief: This will set the target building.
*/

void Board::setTargetBuildingMap(std::vector<LevelMap> buildingMap){
   targetBuildingMap = buildingMap;
}

/**
* This vector will set the start building and the target building
* @brief: This vector will set the start and the target buildings.
*/
std::vector<std::vector<LevelMap>> Board::getBuildingMap(){
   std::vector<std::vector<LevelMap>> vect{ startBuildingMap, targetBuildingMap };
   return vect;
}

/**
* This will change the block in the map
* @brief: This will change the block in the map.
*/
void Board::changeBlockInMap(int row, int col, int type) {
   if(mapType == 0) {
       Block* nodeToChange = classicMap.getNode(row, col);
       nodeToChange->setType(type);
   }
}