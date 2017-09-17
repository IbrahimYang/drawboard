/*****************************************************************************
*******************Ibrahim,CBICR,Tsinghua University**************************
******************************************************************************
File name:    mymouseevent.h
Description:  the head file of mymouseevent.cpp
Author:       Ibrahim Yang
Version:      V1.0
Date:         2017-9-14
History:
*****************************************************************************/
#include "mymouseevent.h"

/*************************************************
Function:     myMouseEvent::myMouseEvent(QWidget *parent) : QGraphicsView(parent)
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
myMouseEvent::myMouseEvent(QWidget *parent) : QGraphicsView(parent)
{

}

/*************************************************
Function:     myMouseEvent::mouseMoveEvent(QMouseEvent *event)
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void myMouseEvent::mouseMoveEvent(QMouseEvent *event)
{
    Event_buf my_event_buf;
    if(mouse_pressed == false)
    {
        return;
    }
    else
    {
        QPoint mouse_pos = event->pos();

        my_event_buf.x = mouse_pos.x() - View_X_Offset;
        //x nomalizition
        if(my_event_buf.x < 0)
        {
            my_event_buf.x = 0;

        }
        else if(my_event_buf.x >= View_X_Max)
        {
            my_event_buf.x = View_X_Max-1;
        }
        my_event_buf.y = mouse_pos.y() - View_Y_Offset;
        //y nomalizition
        if(my_event_buf.y < 0)
        {
            my_event_buf.y = 0;

        }
        else if(my_event_buf.y >= View_Y_Max)
        {
            my_event_buf.y = View_Y_Max-1;
        }
        events_buffer.push_back(my_event_buf);
        emit Mouse_Moved();
    }
}

/*************************************************
Function:     myMouseEvent::mousePressEvent(QMouseEvent *event)
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void myMouseEvent::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_pressed = true;
    }
}

/*************************************************
Function:     myMouseEvent::mouseReleaseEvent(QMouseEvent *event)
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void myMouseEvent::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_pressed = false;
    }
}
