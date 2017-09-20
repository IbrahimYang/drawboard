/*****************************************************************************
*******************Ibrahim,CBICR,Tsinghua University**************************
******************************************************************************
File name:    mymouseevent.cpp
Description:  mymouseevent.cpp
Author:       Ibrahim Yang
Version:      V1.0
Date:         2017-9-14
History:
*****************************************************************************/
#ifndef MYMOUSEEVENT_H
#define MYMOUSEEVENT_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <event.h>

/*include c++11 library*/
#include <iostream>
#include <queue>

#define View_X_Offset 11
#define View_Y_Offset 11
#define View_X_Max 560
#define View_Y_Max 560

using namespace std;

class myMouseEvent : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myMouseEvent(QWidget *parent = nullptr);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    std::vector<Event_buf> left_events_buffer;
    std::vector<Event_buf> right_events_buffer;
    bool left_mouse_pressed = false;
    bool right_mouse_pressed = false;

signals:
    void Mouse_Moved();

private:
};

#endif // MYMOUSEEVENT_H
