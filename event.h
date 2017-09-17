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
#ifndef EVENT_H
#define EVENT_H

/*************************************************
Struct:       Event
Description:  the struct save the event data for dvs128
Calls:        none
Called By:    MyDVS128::run()
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
typedef struct
{
   int x;
   int y;
}Event_buf;

#endif // EVENT_H
