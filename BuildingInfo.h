/**
 * @authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
 * @date: November 10, 2023
 * Purpose @brief: this is the header file for the building info class.
 * It contains the declaration of the constructor and the methods that are used to initialize buildings' coordinates, names, and entrance coordinates. 
*/
#ifndef BUILDINGINFO_H
#define BUILDINGINFO_H
#include <string>
#include <vector>

class BuildingInfo {
    public:
        BuildingInfo(){};
        BuildingInfo(std::string name, std::vector<std::pair<int, int>> coordinates, std::pair<int, int> entrance){
            this->name = name;
            this->coordinates = coordinates;
            this->entrance = entrance;
        }

        std::string getName();
        std::vector<std::pair<int, int>> getCoordinates();
        std::pair<int, int> getEntrance();

    private:
        std::string name;
        std::pair<int, int> entrance;
        std::vector<std::pair<int, int>> coordinates;
};

#endif