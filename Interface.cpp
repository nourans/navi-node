/**
 * @authors Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
 * @brief Implements core functions and visibility within the UI.
 * Date: November 28, 2023
*/

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>
#include <Wt/WImage.h>
#include <Wt/WLink.h>
#include <vector>
#include "Interface.h"

/**
 * @brief This constructor initializes the application's display screen.
 * @param env, provides application information to the client regarding the environment.
*/
Interface::Interface(const Wt::WEnvironment& env)
 : WApplication(env)
{
  buildingDictionaryInstance_ = new BuildingDictionary();
  boardInstance_ = new Board();
  logicServerInstance_= new LogicServer(boardInstance_);
  draggable_= 1;
  useStyleSheet("style/interface.css");
  setHeader();
  setIndicatorImage();
  setCampusIndicatorImage();
  setSelectedText();
  setSelectorType();
  setMap();
}

/**
* @brief This function implements the visualization of the algorithm as it searches for the shortest path by colouring the cell.
 * @param visitedNodes, a vector containing all the nodes visited when trying to find the shortest path.
 * @return delay, the number of visited nodes, and the paint delay for each node.
*/
int Interface::paintVisitedNode(std::vector<std::pair<int, int>> visitedNodes) {
  int type = boardInstance_->getMapType();
  int delay = 1;
  for(std::pair<int, int> node: visitedNodes) {
    if(type == 0) {
      std::string delayText = "animation-delay:" + std::to_string(delay * 0.01) + "s";
      mapContainer_->elementAt(node.first, node.second)->setAttributeValue("style", delayText);
      mapContainer_->elementAt(node.first, node.second)->setStyleClass("visited board-cell");
    } else {
      std::string delayText = "animation-delay:" + std::to_string(delay * 0.005) + "s";
      campusMapContainer_->elementAt(node.first, node.second)->setAttributeValue("style", delayText);
      campusMapContainer_->elementAt(node.first, node.second)->setStyleClass("campus-visited campus-board-cell");
    }
    
    delay++;
  }
  return delay;
}

/**
 * @brief This function sets the application header.
*/
void Interface::setHeader()
{
  /*
  * set the header.
  */
  auto headerContainer = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  headerContainer->addStyleClass("header-container");
  auto brandName = headerContainer->addWidget(std::make_unique<Wt::WText>("PathfindingVisualizer"));
  brandName->addStyleClass("brand-name");
  // algorithm selector dropdown
  auto algorithmSelectorPtr = std::make_unique<Wt::WPopupMenu>();
  auto algorithmSelector = algorithmSelectorPtr.get();
  algorithmSelector->addStyleClass("drop-down__menu");

  Wt::WMenuItem *itemOne = algorithmSelector->addItem("Dijkstra Algorithm");
  itemOne->addStyleClass("drop-down__item");
  itemOne->triggered().connect([=] {
      // 0 is dijkstra
      logicServerInstance_->setAlgorithm(0, boardInstance_);
      // change selected text
      selectedText_->setText(getSelectedText());
  });
  algorithmSelector->addSeparator();

  Wt::WMenuItem *itemTwo = algorithmSelector->addItem("A* Search");
  itemTwo->addStyleClass("drop-down__item");
  itemTwo->triggered().connect([=] {
      // 1 is A*
      logicServerInstance_->setAlgorithm(1, boardInstance_);
      // change selected text
      selectedText_->setText(getSelectedText());
  });

  auto algorithmButton = headerContainer->addWidget(std::make_unique<Wt::WPushButton>("Algorithms"));
  algorithmButton->setMenu(move(algorithmSelectorPtr));

  // board selector dropdown
  auto boardSelectorPtr = std::make_unique<Wt::WPopupMenu>();
  auto boardSelector = boardSelectorPtr.get();
  boardSelector->addStyleClass("drop-down__menu");

  Wt::WMenuItem *boardOne = boardSelector->addItem("Classic Board");
  boardOne->addStyleClass("drop-down__item");
  boardOne->triggered().connect([=] {
      int boardType = boardInstance_->getMapType();
      if(boardType != 0) {
        int logicType = logicServerInstance_->getAlgorithmType();
        delete boardInstance_;
        delete logicServerInstance_;
        boardInstance_ = new Board(1);
        logicServerInstance_= new LogicServer(boardInstance_);
        logicServerInstance_->setAlgorithm(logicType, boardInstance_);
        errorMessage_->hide();
        paintCampusMap();
        selectedCampusStartPoint_->setText("Start Building: None");
        selectedCampusTargetPoint_->setText("Target Building: None");
        setStart = true;
        changeSelectorButton_->setText("Set Target Building");
        
        // switch map to classic map
        boardInstance_->switchMap(0);
        mapContainer_->show();
        campusMapContainer_->hide();
        campusIndicatorImageContainer_->hide();
        indicatorImageContainer_->show();
        typeSelectorContainer_->hide();
        clearWallButton_->show();
        clearPathButton_->show();
      }
  });
  boardSelector->addSeparator();

  //Initializes the campus map
  Wt::WMenuItem *boardTwo = boardSelector->addItem("Campus Map");
  boardTwo->addStyleClass("drop-down__item");
  boardTwo->triggered().connect([=] {
    int logicType = logicServerInstance_->getAlgorithmType();
    delete boardInstance_;
    delete logicServerInstance_;
    boardInstance_ = new Board();
    logicServerInstance_= new LogicServer(boardInstance_);
    logicServerInstance_->setAlgorithm(logicType, boardInstance_);
    paintClassicMap();
    setInitialStartAndTargetNode();
    boardInstance_->switchMap(1);
    mapContainer_->hide();
    campusMapContainer_->show();
    campusIndicatorImageContainer_->show();
    typeSelectorContainer_->show();
    indicatorImageContainer_->hide();
    clearWallButton_->hide();
    clearPathButton_->hide();
  });

  //Header to change board type
  auto boardButton = headerContainer->addWidget(std::make_unique<Wt::WPushButton>("Boards"));
  boardButton->setMenu(move(boardSelectorPtr));

  //Visualizes path
  auto visualizeButton_ = headerContainer->addWidget(std::make_unique<Wt::WPushButton>("Visualize!"));
  visualizeButton_->clicked().connect([=] {
    int type = boardInstance_->getMapType();
    if(type == 0) {
      draggable_ = 0;
      int startPointRow = boardInstance_->getMap()->getStartPoint()->getRow();
      int startPointCol = boardInstance_->getMap()->getStartPoint()->getColumn();
      int targetPointRow = boardInstance_->getMap()->getTargetPoint()->getRow();
      int targetPointCol = boardInstance_->getMap()->getTargetPoint()->getColumn();
      WImage* startContainer = (WImage*) (mapContainer_->elementAt(startPointRow, startPointCol)->children()[0]->children()[0]);
      startContainer->unsetDraggable();
      WImage* targetContainer = (WImage*) (mapContainer_->elementAt(targetPointRow, targetPointCol)->children()[0]->children()[0]);
      targetContainer->unsetDraggable();
      std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> result = logicServerInstance_->runAlgorithm();
      int delay = paintVisitedNode(result.first);
      paintShortestPathNode(result.second, delay);
    } else {
      if(selectedCampusStartPoint_->text() == "Start Building: None" || selectedCampusTargetPoint_->text() == "Target Building: None") {
        errorMessage_->show();
        return;
      }
      int startPointRow = boardInstance_->getMap()->getStartPoint()->getRow();
      int startPointCol = boardInstance_->getMap()->getStartPoint()->getColumn();
      int targetPointRow = boardInstance_->getMap()->getTargetPoint()->getRow();
      int targetPointCol = boardInstance_->getMap()->getTargetPoint()->getColumn();

      std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> result = logicServerInstance_->runAlgorithm();

      int delay = paintVisitedNode(result.first);
      paintShortestPathNode(result.second, delay);
    }
  });

  //Clears board
  auto clearBoardButton_ = headerContainer->addWidget(std::make_unique<Wt::WPushButton>("Clear Board"));
  clearBoardButton_->clicked().connect([=] {
    int mapType = boardInstance_->getMapType();
    int type = logicServerInstance_->getAlgorithmType();
    delete boardInstance_;
    delete logicServerInstance_;
    if(mapType == 0) {
      boardInstance_ = new Board();
      logicServerInstance_= new LogicServer(boardInstance_);
      logicServerInstance_->setAlgorithm(type, boardInstance_);
      paintClassicMap();
      setInitialStartAndTargetNode();
    } else {
      boardInstance_ = new Board(1);
      logicServerInstance_= new LogicServer(boardInstance_);
      logicServerInstance_->setAlgorithm(type, boardInstance_);
      paintCampusMap();
      selectedCampusStartPoint_->setText("Start Building: None");
      selectedCampusTargetPoint_->setText("Target Building: None");
      setStart = true;
      changeSelectorButton_->setText("Set Target Building");
      errorMessage_->hide();
    }
  });

  //Clears walls
  clearWallButton_ = headerContainer->addWidget(std::make_unique<Wt::WPushButton>("Clear Walls & Weight"));
  clearWallButton_->clicked().connect([=] {
    int startRow = boardInstance_->getMap()->getStartPoint()->getRow();
    int startCol = boardInstance_->getMap()->getStartPoint()->getColumn();
    int targetRow = boardInstance_->getMap()->getTargetPoint()->getRow();
    int targetCol = boardInstance_->getMap()->getTargetPoint()->getColumn();
    int type = logicServerInstance_->getAlgorithmType();
    delete boardInstance_;
    delete logicServerInstance_;
    boardInstance_ = new Board();
    logicServerInstance_= new LogicServer(boardInstance_);
    logicServerInstance_->setAlgorithm(type, boardInstance_);
    paintClassicMap();
    setStartAndTargetNode(startRow, startCol, targetRow, targetCol, boardInstance_);
  });

  //Clears path visualizations
  clearPathButton_ = headerContainer->addWidget(std::make_unique<Wt::WPushButton>("Clear Path"));
  clearPathButton_->clicked().connect([=] {
    std::vector<std::pair<int, int>> walls = boardInstance_->getMap()->getWallsInfo();
    int startRow = boardInstance_->getMap()->getStartPoint()->getRow();
    int startCol = boardInstance_->getMap()->getStartPoint()->getColumn();
    int targetRow = boardInstance_->getMap()->getTargetPoint()->getRow();
    int targetCol = boardInstance_->getMap()->getTargetPoint()->getColumn();
    int type = logicServerInstance_->getAlgorithmType();
    delete boardInstance_;
    delete logicServerInstance_;
    boardInstance_ = new Board();
    logicServerInstance_= new LogicServer(boardInstance_);
    logicServerInstance_->setAlgorithm(type, boardInstance_);
    paintClassicMap();
    setStartAndTargetNode(startRow, startCol, targetRow, targetCol, boardInstance_);
    paintWalls(walls, boardInstance_);
  });
}

/**
 * @brief This method sets the start node and target node icons (target and arrow)
*/
void Interface::setIndicatorImage() {
  indicatorImageContainer_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  indicatorImageContainer_->addStyleClass("indicator-container");
  indicatorImageContainer_->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("images/triangletwo-right.svg")))->addStyleClass("element-space");
  indicatorImageContainer_->addWidget(std::make_unique<Wt::WText>("Start Node"))->addStyleClass("gap-right");
  indicatorImageContainer_->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("images/circle.svg")))->addStyleClass("element-space");
  indicatorImageContainer_->addWidget(std::make_unique<Wt::WText>("Target Node"))->addStyleClass("gap-right");
  indicatorImageContainer_->addWidget(std::make_unique<Wt::WText>(""))->addStyleClass("block unvisited");
  indicatorImageContainer_->addWidget(std::make_unique<Wt::WText>("Unvisited Node"))->addStyleClass("gap-right");
  indicatorImageContainer_->addWidget(std::make_unique<Wt::WText>(""))->addStyleClass("block visited");
  indicatorImageContainer_->addWidget(std::make_unique<Wt::WText>("Visited Node"))->addStyleClass("gap-right");
  indicatorImageContainer_->addWidget(std::make_unique<Wt::WText>(""))->addStyleClass("block shortest-path-example");
  indicatorImageContainer_->addWidget(std::make_unique<Wt::WText>("Shortest-path Node"));
}

/**
 * @brief This method highlights the start and target buildings in the campus maps.
*/
void Interface::setCampusIndicatorImage() {
  campusIndicatorImageContainer_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  campusIndicatorImageContainer_->addStyleClass("indicator-container");
  campusIndicatorImageContainer_->addWidget(std::make_unique<Wt::WText>(""))->addStyleClass("block start_color");
  campusIndicatorImageContainer_->addWidget(std::make_unique<Wt::WText>("Start Node"))->addStyleClass("gap-right");
  campusIndicatorImageContainer_->addWidget(std::make_unique<Wt::WText>(""))->addStyleClass("block target_color");
  campusIndicatorImageContainer_->addWidget(std::make_unique<Wt::WText>("Target Node"))->addStyleClass("gap-right");
  campusIndicatorImageContainer_->addWidget(std::make_unique<Wt::WText>(""))->addStyleClass("block unvisited");
  campusIndicatorImageContainer_->addWidget(std::make_unique<Wt::WText>("Unvisited Node"))->addStyleClass("gap-right");
  campusIndicatorImageContainer_->addWidget(std::make_unique<Wt::WText>(""))->addStyleClass("block visited");
  campusIndicatorImageContainer_->addWidget(std::make_unique<Wt::WText>("Visited Node"))->addStyleClass("gap-right");
  campusIndicatorImageContainer_->addWidget(std::make_unique<Wt::WText>(""))->addStyleClass("block shortest-path-example");
  campusIndicatorImageContainer_->addWidget(std::make_unique<Wt::WText>("Shortest-path Node"));
  campusIndicatorImageContainer_->hide();
}

/**
 * @brief This method sets the building name to the chosen start and target building's names.
*/
void Interface::setSelectedText() {
   auto selectedTextContainer = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
   selectedTextContainer->addStyleClass("selected-text");
   selectedText_ = selectedTextContainer->addWidget(std::make_unique<Wt::WText>(getSelectedText()));
}

/**
 * @brief This method sets the selector type to identify the start and target buildings.
*/
void Interface::setSelectorType() {
  typeSelectorContainer_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  typeSelectorContainer_->addStyleClass("selectorContainer");
  selectedCampusStartPoint_ = typeSelectorContainer_->addWidget(std::make_unique<Wt::WText>("Start Building: None"));
  selectedCampusStartPoint_->setInline(false);
  selectedCampusTargetPoint_ = typeSelectorContainer_->addWidget(std::make_unique<Wt::WText>("Target Building: None"));
  selectedCampusTargetPoint_->setInline(false);
  changeSelectorButton_ = typeSelectorContainer_->addWidget(std::make_unique<Wt::WPushButton>("Set Target Building"));
  changeSelectorButton_->addStyleClass("toggleSelectorButton");
  changeSelectorButton_->clicked().connect([=] {
    setStart = !setStart;
    if(setStart) {
      changeSelectorButton_->setText("Set Target Building");
    } else {
      changeSelectorButton_->setText("Set Start Building");
    }
  });

  //Error message if not both a start and target building are selected
  errorMessage_ = typeSelectorContainer_->addWidget(std::make_unique<Wt::WText>("Please select both Start Building and Target Building!"));
  errorMessage_->addStyleClass("errorMessage");
  errorMessage_->setInline(false);
  errorMessage_->hide();
  typeSelectorContainer_->hide(); 
}

/**
 * @brief This method sets the map to be the classic or campus map.
*/
void Interface::setMap() {
  auto boardContainer = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  boardContainer->setStyleClass("map-container");
  mapContainer_ = boardContainer->addWidget(std::make_unique<Wt::WTable>());
  mapContainer_->setStyleClass("table-background");
  paintClassicMap();
  setInitialStartAndTargetNode();

  campusMapContainer_= boardContainer->addWidget(std::make_unique<Wt::WTable>());
  paintCampusMap();
  campusMapContainer_->hide();
}

/**
 * @brief This method colours in/highlights the buildings on the campus map.
 * @param walls, the vector of the building coordinates.
 * @param board, an instance of the board class.
*/
void Interface::paintWalls(std::vector<std::pair<int, int>> walls, Board* board) {
  for(std::pair<int, int> wall: walls) {
    board->changeBlockInMap(wall.first, wall.second, 5);  
    mapContainer_->elementAt(wall.first, wall.second)->children()[0]->addStyleClass("wall");
    mapContainer_->elementAt(wall.first, wall.second)->removeStyleClass("unvisited");
    mapContainer_->elementAt(wall.first, wall.second)->addStyleClass("wall");
  }
}

/**
* @brief This method illustrates the wall functionality on the classic map.
*/
void Interface::paintClassicMap() {
  draggable_ = 1;
  mapContainer_->clear();
  mapContainer_->setStyleClass("board");
  for (int i = 0; i < 20; ++i) {
    for(int j = 0; j < 52; ++j){
      auto dropContainer = mapContainer_->elementAt(i, j)->addWidget(std::make_unique<CustomDropContainerWidget>(boardInstance_));
      dropContainer->setStyleClass("board-cell");
      mapContainer_->elementAt(i, j)->setStyleClass("unvisited board-cell");
      mapContainer_->elementAt(i, j)->mouseDragged().connect([=] {
        if(draggable_) {
          int startRow = boardInstance_->getMap()->getStartPoint()->getRow();
          int startCol = boardInstance_->getMap()->getStartPoint()->getColumn();
          int targetRow = boardInstance_->getMap()->getTargetPoint()->getRow();
          int targetCol = boardInstance_->getMap()->getTargetPoint()->getColumn();
          bool isStart = startRow == i && startCol == j;
          bool isTarget = targetRow == i && targetCol == j;
          // update wall infomration to board class
          if(!isStart && !isTarget){
            boardInstance_->changeBlockInMap(i, j, 5);
            dropContainer->addStyleClass("wall");
            mapContainer_->elementAt(i, j)->removeStyleClass("unvisited");
            mapContainer_->elementAt(i, j)->addStyleClass("wall");
          }
        }
      });
    }
  }
}

/**
 * @brief This method displays the start and target building names and highlights them when clicked.
*/
void Interface::paintCampusMap() {
  campusMapContainer_->clear();
  campusMapContainer_->setStyleClass("campus-board");
  for (int i = 0; i < 200; ++i) {
    for(int j = 0; j < 168; ++j){
      auto child = campusMapContainer_->elementAt(i, j)->addWidget(std::make_unique<Wt::WContainerWidget>());
      child->setStyleClass("campus-board-cell");
      campusMapContainer_->elementAt(i, j)->setStyleClass("campus-board-cell");
    }
  }
  std::vector<BuildingInfo> buildings = buildingDictionaryInstance_->getBuildings();

  for(BuildingInfo building: buildings) {
    std::vector<std::pair<int, int>> coordinates = building.getCoordinates();
    std::string name = building.getName();
    std::pair<int, int> entrance = building.getEntrance();
    for(std::pair<int, int> coordinate: coordinates) {
      // add click method, set attribute buildingName
      campusMapContainer_->elementAt(coordinate.first, coordinate.second)->setAttributeValue("buildingName", name);
      campusMapContainer_->elementAt(coordinate.first, coordinate.second)->clicked().connect([=] {
      errorMessage_->hide();
      
      if(setStart) {
        if(startCoordinates.size() != 0) {
            clearBuildingHighlight(startCoordinates);       
        }
        startCoordinates = coordinates;
        std::string text = "Start Building: " + name;
        selectedCampusStartPoint_->setText(text);
        boardInstance_->getMap()->setStartPoint(entrance.first, entrance.second);
      } else {
        if(targetCoordinates.size() != 0) {
            clearBuildingHighlight(targetCoordinates);       
        }
        targetCoordinates = coordinates;
        std::string text = "Target Building: " + name;
        selectedCampusTargetPoint_->setText(text);
        boardInstance_->getMap()->setTargetPoint(entrance.first, entrance.second);
      }
        
        for(std::pair<int, int> coordinate: coordinates) {
          if(setStart){
            campusMapContainer_->elementAt(coordinate.first, coordinate.second)->addStyleClass("start_color");
          }else{
            campusMapContainer_->elementAt(coordinate.first, coordinate.second)->addStyleClass("target_color");
          }   
        }
      });
    }
  }
}

/**
 * @brief This method clears the highlight on the selected building.
 * @param coordinates, the coordinates of the building highlighted.
*/
void Interface::clearBuildingHighlight(std::vector<std::pair<int, int>> coordinates) {
  for(std::pair<int, int> coordinate: coordinates) {
    campusMapContainer_->elementAt(coordinate.first, coordinate.second)->removeStyleClass("start_color");
    campusMapContainer_->elementAt(coordinate.first, coordinate.second)->removeStyleClass("target_color");
  }
}

/**
 * @brief This method sets the initial start and target node to a random position on the grid for the classic map.
*/
void Interface::setInitialStartAndTargetNode() {
  auto startIconContainer = mapContainer_->elementAt(10, 12)->children();
  auto startIcon = ((CustomDropContainerWidget *)startIconContainer.front())->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("images/triangletwo-right.svg")));
  startIcon->setAlternateText("Start-Icon");
  auto endIconContainer = mapContainer_->elementAt(10, 40)->children();
  auto endIcon = ((CustomDropContainerWidget *)endIconContainer.front())->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("images/circle.svg")));
  endIcon->setAlternateText("End-Icon");
  startIcon->setDraggable("WImage");
  endIcon->setDraggable("WImage");
}
/**
 * @brief This method sets the start and target nodes on the classic map.
 * @param startRow: The row of the starting node.
 * @param startCol: The column of the starting node.
 * @param targetRow: The row of the target node.
 * @param targetCol: The column of the target node.
 * @param board: An instance of the board class.
*/
void Interface::setStartAndTargetNode(int startRow, int startCol, int targetRow, int targetCol, Board* board) {
  auto startIconContainer = mapContainer_->elementAt(startRow, startCol)->children();
  auto startIcon = ((CustomDropContainerWidget *)startIconContainer.front())->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("images/triangletwo-right.svg")));
  startIcon->setAlternateText("Start-Icon");
  board->getMap()->setStartPoint(startRow, startCol);
  auto endIconContainer = mapContainer_->elementAt(targetRow, targetCol)->children();
  auto endIcon = ((CustomDropContainerWidget *)endIconContainer.front())->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("images/circle.svg")));
  endIcon->setAlternateText("End-Icon");
  startIcon->setDraggable("WImage");
  endIcon->setDraggable("WImage");
  board->getMap()->setTargetPoint(targetRow, targetCol);
}

/**
 * @brief This method displays a message based on the algorithm selected.
 * @return A string informing you what algorithm you are using.
*/
std::string Interface::getSelectedText() {
 int algorithmSelected = logicServerInstance_->getAlgorithmType();
 switch(algorithmSelected) {
   case 0:
     return "Dijkstra's Algorithm <b>guarantees</b> the shortest path";
   case 1:
     return "A* Search <b>guarantees</b> the shortest path";
   default:
     return "Pick an algorithm and visualize it!";
 }
}

/**
 * @brief This method paints the cells based on the type of cell.
 * @param node, the cell to be painted.
 * @param type, the type of cell.
*/
void Interface::paintCell(Block node, int type) {
 int row = node.getRow();
 int col = node.getColumn();
 if (type == 0){
   // type 0 means shortestPath
   mapContainer_->elementAt(row, col)->setStyleClass("shortest-path board-cell");
 } else if (type == 1){
   // type 1 means visited node
   mapContainer_->elementAt(row, col)->setStyleClass("visited board-cell");
 } else if (type == 2){
   // type 2 mean unvisited node
   mapContainer_->elementAt(row, col)->setStyleClass("unvisited board-cell");
 }
}

/**
 * @brief Visualizes the shortest path on the application grid.
 * @param shortestPath, a vector containing the shortest path from the start to destination nodes.
 * @param delay, the delay time to colour the node.
*/
void Interface::paintShortestPathNode(std::vector<std::pair<int, int>> shortestPath, int delay) {
  int type = boardInstance_->getMapType();
  for(std::pair<int, int> node: shortestPath) {
    if(type == 0) {
      std::string delayText = "transition-delay:" + std::to_string(delay * 0.01) + "s";
      auto children = mapContainer_->elementAt(node.first, node.second)->children();
      children[0]->setAttributeValue("style", delayText);
      mapContainer_->elementAt(node.first, node.second)->addStyleClass("shortest-path");
    } else {
      std::string delayText = "transition-delay:" + std::to_string(delay * 0.005) + "s";
      auto children = campusMapContainer_->elementAt(node.first, node.second)->children();
      children[0]->setAttributeValue("style", delayText);
      campusMapContainer_->elementAt(node.first, node.second)->addStyleClass("shortest-path");
    }
    delay++;
  }
}
