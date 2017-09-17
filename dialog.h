/*****************************************************************************
*******************Ibrahim,CBICR,Tsinghua University**************************
******************************************************************************
File name:    dialog.h
Description:  the header file of dialog.cpp
Author:       Ibrahim Yang
Version:      V1.0
Date:         2017-9-14
History:
*****************************************************************************/
#ifndef DIALOG_H
#define DIALOG_H

/*include local Qt library*/
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QEvent>
#include <QMouseEvent>
#include <QImage>
#include <QDebug>

/*include local my head file library*/
#include <mymouseevent.h>

/*include local opencv library*/
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/*include local c++ library*/
#include <iostream>

using namespace std;
using namespace cv;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QImage number_image = QImage(560,560,QImage::Format_Grayscale8);
    Mat QImage2cvMat(QImage image);
    QImage cvMat2QImage(const Mat &mat);

private slots:
    void on_upload_clicked();

    void on_download_clicked();

    void on_start_clicked();

    void on_stop_clicked();

    void in_Mouse_Moved();

private:
    Ui::Dialog *ui;
    bool mouse_pressed = false;
    QGraphicsScene *plotboard;

};

#endif // DIALOG_H
