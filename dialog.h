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

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

/*include local my head file library*/
#include <mymouseevent.h>

/*include local opencv library*/
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

/*include local c++ library*/
//#include <iostream>

//using namespace std;
//using namespace cv;

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QImage number_image = QImage(560,560,QImage::Format_RGB32);
//    Mat QImage2cvMat(QImage image);
//    QImage cvMat2QImage(const Mat &mat);

    //QBarSet *set0;
    QBarSeries *series;
    QChart *chart;
    QBarCategoryAxis *X_axis;
    QStringList categories;
    void chart_init();

private slots:
    void on_upload_clicked();

    void on_download_clicked();

    void on_start_clicked();

    void on_clear_clicked();

    void in_Mouse_Moved();

private:
    Ui::Dialog *ui;
    bool mouse_pressed = false;
    QGraphicsScene *plotboard;
};

#endif // DIALOG_H
