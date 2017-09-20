/*****************************************************************************
*******************Ibrahim,CBICR,Tsinghua University**************************
******************************************************************************
File name:    dialog.cpp
Description:  dialog.cpp
Author:       Ibrahim Yang
Version:      V1.0
Date:         2017-9-14
History:
*****************************************************************************/
#include "dialog.h"
#include "ui_dialog.h"

#define draw_inter_factor 30
#define clear_inter_factor 50

/*************************************************
Function:     Dialog::Dialog(QWidget *parent) :
                      QDialog(parent),
                      ui(new Ui::Dialog)
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    /*init parameter*/
    number_image.fill(Qt::white);
    number_image_real.fill(Qt::black);

    /*ui setup*/
    ui->setupUi(this);

    /*chart graphicsView_2 init*/
    this->chart_init();

    /*plotboard graphicsView setup*/
    plotboard  = new QGraphicsScene(this);
    //plotboard->setSceneRect(0,0,560,560);

    ui->graphicsView->setScene(plotboard);

    plotboard->clear();
    plotboard->addPixmap(QPixmap::fromImage(number_image));

    /*connect signal and slot*/
    connect(ui->graphicsView,SIGNAL(Mouse_Moved()),this,SLOT(in_Mouse_Moved()));
}

/*************************************************
Function:     Dialog::~Dialog()
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
Dialog::~Dialog()
{
    delete ui;
}

/*************************************************
Function:     Dialog::on_upload_clicked()
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void Dialog::on_upload_clicked()
{
    this->chart_show();
}

/*************************************************
Function:     Dialog::on_download_clicked()
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void Dialog::on_download_clicked()
{
    this->chart_init();
}

/*************************************************
Function:     Dialog::on_start_clicked()
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void Dialog::on_start_clicked()
{
    QImage number_image_out;
    uchar *number_image_out_8;
    number_image_out = number_image_real.scaled(28, 28, Qt::KeepAspectRatioByExpanding);

    for(int counter_y = 0; counter_y < 28; counter_y++)
    {
        number_image_out_8 = number_image_out.scanLine(counter_y);
        for(int counter_x = 0; counter_x < 28; counter_x++)
        {
            int gray_8 = number_image_out_8[ counter_x ];
            if(gray_8 % 100 != 0)
            {
                std::cout << gray_8 << ",";
            }
            else if(gray_8 % 10 != 0)
            {
                std::cout << gray_8 << ", ";
            }
            else
            {
                std::cout << gray_8 << ",  ";
            }
        }
        std::cout << endl;
    }
    std::cout << endl;
}

/*************************************************
Function:     Dialog::on_stop_clicked()
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void Dialog::on_clear_clicked()
{
    plotboard->clear();
    number_image.fill(Qt::white);
    number_image_real.fill(Qt::black);
    plotboard->addPixmap(QPixmap::fromImage(number_image));
}

/*************************************************
Function:     Dialog::in_Mouse_Moved()
Description:  none
Calls:        none
Called By:    all
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void Dialog::in_Mouse_Moved()
{
    QRgb value_blue = qRgb(42, 154, 221),
         value_white = qRgb(255, 255, 255),
         value_black = qRgb(0, 0, 0);
    plotboard->clear();
    if(ui->graphicsView->left_mouse_pressed == true)
    {
        for(int counter_x = 0; counter_x < draw_inter_factor; counter_x++)
        {
            for(int counter_y = 0; counter_y < draw_inter_factor; counter_y++)
            {
                number_image.setPixel((ui->graphicsView->left_events_buffer[0].x) + counter_x,(ui->graphicsView->left_events_buffer[0].y) + counter_y,value_blue);
                number_image_real.setPixel((ui->graphicsView->left_events_buffer[0].x) + counter_x,(ui->graphicsView->left_events_buffer[0].y) + counter_y,value_white);
            }
        }
        ui->graphicsView->left_events_buffer.clear();
    }
    else if(ui->graphicsView->right_mouse_pressed == true)
    {
        for(int counter_x = 0; counter_x < clear_inter_factor; counter_x++)
        {
            for(int counter_y = 0; counter_y < clear_inter_factor; counter_y++)
            {
                number_image.setPixel((ui->graphicsView->right_events_buffer[0].x) + counter_x,(ui->graphicsView->right_events_buffer[0].y) + counter_y,value_white);
                number_image_real.setPixel((ui->graphicsView->right_events_buffer[0].x) + counter_x,(ui->graphicsView->right_events_buffer[0].y) + counter_y,value_black);
            }
        }
        ui->graphicsView->right_events_buffer.clear();
    }
    else
    {
        return;
    }
    plotboard->addPixmap(QPixmap::fromImage(number_image));
}

/*************************************************
Function:     Dialog::in_chart_show()
Description:  Image2cvMat
Calls:        none
Called By:    none
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void Dialog::in_chart_show()
{

}

/*************************************************
Function:     Dialog::chart_init()
Description:  chart init
Calls:        none
Called By:    none
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void Dialog::chart_init()
{
    QBarSeries *series = new QBarSeries();
    QChart *chart = new QChart();
    QBarCategoryAxis *X_axis = new QBarCategoryAxis();
    QStringList categories_x;
    QBarSet *set0 = new QBarSet("Probability");
    *set0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;
    series->append(set0);
    chart->addSeries(series);
    chart->createDefaultAxes();

    chart->setTitle("Tianjic computation result");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    categories_x << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
    X_axis->append(categories_x);
    chart->createDefaultAxes();
    chart->setAxisX(X_axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    ui->graphicsView_2->setChart(chart);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->show();
}

/*************************************************
Function:     Dialog::chart_init()
Description:  chart init
Calls:        none
Called By:    none
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
void Dialog::chart_show()
{
    QBarSeries *series = new QBarSeries();
    QChart *chart = new QChart();
    QBarCategoryAxis *X_axis = new QBarCategoryAxis();
    QStringList categories_x;
    QBarSet *set0 = new QBarSet("Probability");

    *set0 << 0.0001 << 0.0044 << 0.054 << 0.242 << 0.4 << 0.242 << 0.054 << 0.0044 << 0.0001 << 0;
    series->append(set0);
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Tianjic computation result");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    categories_x << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
    X_axis->append(categories_x);
    chart->createDefaultAxes();
    chart->setAxisX(X_axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    ui->graphicsView_2->setChart(chart);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->show();
}
