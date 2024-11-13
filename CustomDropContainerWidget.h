/**
* Authors: Alysha Aul, Nandhitha Krishnan, Paul Rodgers, Nouran Sakr, Chun Yang
* Date: November 28, 2023
* Purpose: To act as a Container that accept drag and drop the start point and end point.
*/
#ifndef CUSTOMDROPCONTAINER_WIDGET_H
#define CUSTOMDROPCONTAINER_WIDGET_H

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WWidget.h>
#include <Wt/WTableCell.h>
#include <Wt/WImage.h>
#include "Board.h"

using namespace Wt;

class CustomDropContainerWidget: public WContainerWidget
{
    public:
        CustomDropContainerWidget (Board* board);
        void dropEvent(WDropEvent event);

    private:
        Board         *boardInstance_;
};

#endif