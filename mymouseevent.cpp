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
    if(left_mouse_pressed == false && right_mouse_pressed == false)
    {
        return;
    }
    else if(left_mouse_pressed == true && right_mouse_pressed == false)
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
        left_events_buffer.push_back(my_event_buf);
        //left_events_buffer_all.push_back(my_event_buf);
        emit Mouse_Moved();
    }
    else if(left_mouse_pressed == false && right_mouse_pressed == true)
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
        right_events_buffer.push_back(my_event_buf);
        //right_events_buffer_all.push_back(my_event_buf);
        emit Mouse_Moved();
    }
    else
    {
        return;
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
    Event_buf my_event_buf;
    if(event->button() == Qt::LeftButton)
    {
        left_mouse_pressed = true;
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
        left_events_buffer.push_back(my_event_buf);
        //left_events_buffer_all.push_back(my_event_buf);
        emit Mouse_Moved();
    }
    else if(event->button() == Qt::RightButton)
    {
        right_mouse_pressed =true;
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
        right_events_buffer.push_back(my_event_buf);
        //right_events_buffer_all.push_back(my_event_buf);
        emit Mouse_Moved();
    }
    else
    {
        return;
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
        left_mouse_pressed = false;
    }
    else if(event->button() == Qt::RightButton)
    {
        right_mouse_pressed = false;
    }
    else
    {
        return;
    }
}
