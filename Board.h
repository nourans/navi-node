/**
* Authors @authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 7, 2023
* Purpose @brief:This is the header file for the board.cpp file
*/

#ifndef BOARD_H
#define BOARD_H
#pragma once
#include <string>
#include <vector>
#include <Wt/WContainerWidget.h>
#include "LevelMap.h"

class Board
{
    public:
        Board(int type = 0) {
            // the initial board should be classic map
            setBoardMapType(type);              
            classicMap = LevelMap();
            campusMap = LevelMap(1);
        }
        void initCampusMap();
        void switchMap(int type);
        void setBoardMapType(int num);
        int getMapType();
        LevelMap* getMap();
        void changeBlockInMap(int row, int col, int type);
        std::vector<std::vector<LevelMap>> getBuildingMap();
        void setStartBuildingMap(std::vector<LevelMap> buildingMap);
        void setTargetBuildingMap(std::vector<LevelMap> buildingMap);

    private:
        // type 0 is classic map, type 1 is campus map
        int mapType;
        // this is the flat map for classic mode
        LevelMap classicMap;
        // this is the flat map for general campus map
        LevelMap campusMap;
        // this is the specific building map
        std::vector<LevelMap> startBuildingMap;
        // this is the specific building map
        std::vector<LevelMap> targetBuildingMap;    
};

#endif