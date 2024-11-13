/**
@authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
@date: November 10, 2023
Purpose @brief:  This is the header file for the BuildingDictionary class. It contains the declaration of the constructor
and the methods that are used to initialize the map of buildings and their locations
*/
#ifndef BUILDINGDICTIONARY_H
#define BUILDINGDICTIONARY_H
#include "BuildingInfo.h"
class BuildingDictionary {
    public:
        BuildingDictionary() {
            initializeMapBuildingLocations();
        }
        std::vector<std::pair<int,int>> getCoordinates(std::string buildingName);
        std::vector<BuildingInfo> getBuildings();
    private:
        std::vector<BuildingInfo> buildings;
        void initializeMapBuildingLocations();
};

#endif