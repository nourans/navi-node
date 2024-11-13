/**
* Authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 7, 2023
* Purpose: To act as a communication link between the Algorithm and Interface classes.
*/

#include "LogicServer.h"
#include "Interface.h"
using namespace std;

/**
* Sets the algorithm type based on drop down menu selection.
* @param type: The algorithm chosen; 0 for Dikjstra, 1 for A*.
*/
void LogicServer::setAlgorithm(int type, Board* board) {
    AlgorithmFactory* factory;
    if(type != this->type) {
        this->type = type;
        delete algorithmInstance_;
        algorithmInstance_ = factory->createAlgorithmInstance(type, board);
    }
}

/**
 * Returns the algorithm type.
 * @return type: the algorithm type.
*/
int LogicServer::getAlgorithmType() {
   return type;
}

/**
* Runs the search algorithm based on type.
* @param mapContainer: The map instance.
*/
pair<vector<pair<int, int>>, vector<pair<int, int>>> LogicServer::runAlgorithm() {
    return algorithmInstance_->runAlgorithm();
}