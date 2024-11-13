/**
* Authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 28, 2023
* Purpose: To act as a Container that accept drag and drop the start point and end point.
*/

#include "CustomDropContainerWidget.h"

/**
* Class constructor for make drop and drag possible for the node 
* It will accept dropped image
*/
CustomDropContainerWidget::CustomDropContainerWidget(Board* board)
{
    boardInstance_= board;
    acceptDrops("WImage");
    setInline(false);
}

/**
* Drop event Method: when we actually drop the item we need to check if we can drop or not.
* @param event: the drop event which contains the information about dropped item.
*/
void CustomDropContainerWidget::dropEvent(WDropEvent event)
{
    if(event.mimeType() == "WImage"){
        WImage *child = static_cast<WImage*>(event.source());
        WContainerWidget *parent = static_cast<WContainerWidget*>(child->parent());
        WTableCell *parentCell = static_cast<WTableCell*>(this->parent());
        int row = parentCell->row();
        int column = parentCell->column();
        int type = boardInstance_->getMap()->getNode(row, column)->getType();
        // if it is not a wall block, then we can drop
        if(type != 5) {
            parent->removeChild(child);
            if(child->alternateText() == "Start-Icon"){
                WImage *temp = addWidget(std::make_unique<Wt::WImage>(Wt::WLink("images/triangletwo-right.svg")));
                temp->setDraggable("WImage");
                temp->setAlternateText("Start-Icon");
                // modify start point of map in board class 
                boardInstance_->getMap()->setStartPoint(row, column);
            }else if(child->alternateText() == "End-Icon") {
                WImage *temp = addWidget(std::make_unique<Wt::WImage>(Wt::WLink("images/circle.svg")));
                temp->setDraggable("WImage");
                temp->setAlternateText("End-Icon"); 
                // modify end point of map in board class 
                boardInstance_->getMap()->setTargetPoint(row, column);
            }
        }
    }
}