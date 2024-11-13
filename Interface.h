/**
 * @authors Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
 * @brief Header file to declare class functions and variables to be implemented within the interface.
 * Date: November 28, 2023
*/
#ifndef INTERFACE_H
#define INTERFACE_H

#pragma once
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <string>
#include <vector>
#include "Algorithm.h"
#include "CustomDropContainerWidget.h"
#include "Block.h"
#include "LogicServer.h"
#include "BuildingDictionary.h"

typedef struct Coordinate
{
    int row;
    int col;
} Coordinate;

class Interface : public Wt::WApplication
{
public:
    Interface(const Wt::WEnvironment& env);
    void          paintCell(Block node, int type);

private:
    BuildingDictionary               *buildingDictionaryInstance_;
    LogicServer                      *logicServerInstance_;
    Wt::WText                        *selectedText_;
    Wt::WTable                       *mapContainer_;
    Wt::WTable                       *campusMapContainer_;
    Wt::WContainerWidget             *indicatorImageContainer_;
    Wt::WContainerWidget             *campusIndicatorImageContainer_;
    Wt::WContainerWidget             *typeSelectorContainer_;
    Wt::WPushButton                  *clearWallButton_;
    Wt::WPushButton                  *clearPathButton_;
    Wt::WPushButton                  *changeSelectorButton_;
    Board                            *boardInstance_;
    int                              draggable_;
    //std::vector<std::pair<int, int>> paths;
    Wt::WText                        *selectedCampusStartPoint_;
    Wt::WText                        *selectedCampusTargetPoint_;
    Wt::WText                        *errorMessage_;
    bool                             setStart=true;
    std::vector<std::pair<int, int>> startCoordinates;
    std::vector<std::pair<int, int>> targetCoordinates;

    void                             setHeader();
    void                             setIndicatorImage();
    void                             setCampusIndicatorImage();
    void                             setSelectedText();
    void                             setSelectorType();
    void                             setMap();
    void                             paintWalls(std::vector<std::pair<int, int>> walls, Board* board);
    void                             paintClassicMap();
    void                             paintCampusMap();
    void                             clearBuildingHighlight(std::vector<std::pair<int, int>> coordinates);
    void                             setInitialStartAndTargetNode();
    void                             setStartAndTargetNode(int startRow, int startCol, int targetRow, int targetCol, Board* board);
    std::string                      getSelectedText();
    void                             paintShortestPathNode(std::vector<std::pair<int, int>> shortestPath, int delay = 0);
    int                              paintVisitedNode(std::vector<std::pair<int, int>> visitedNodes);
};
#endif
