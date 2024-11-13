#include "BuildingInfo.h"

/**
 * Get the name of building
 * @return name: the name of building.
 * 
*/
std::string BuildingInfo::getName() {
    return name;
}

/**
 * Get the coordinates of building
 * @return coordinates: the coordinates of building.
 * 
*/
std::vector<std::pair<int, int>> BuildingInfo::getCoordinates() {
    return coordinates;
}

/**
 * Get the entrance location of building
 * @return entrance: the entance location of building.
 * 
*/
std::pair<int, int> BuildingInfo::getEntrance() {
    return entrance;
}