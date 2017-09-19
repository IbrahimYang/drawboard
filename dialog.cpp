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

#define draw_inter_factor 25
#define clear_inter_factor 50

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    /*init parameter*/
    number_image.fill(Qt::white);

    /*ui setup*/
    ui->setupUi(this);

    /*chart graphicsView_2 init*/
    this->chart_init();

    /*plotboard graphicsView setup*/
    plotboard  = new QGraphicsScene(this);

    ui->graphicsView->setScene(plotboard);
    ui->graphicsView_2->setChart(chart);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->show();

    plotboard->clear();
    plotboard->addPixmap(QPixmap::fromImage(number_image));

    /*connect signal and slot*/
    connect(ui->graphicsView,SIGNAL(Mouse_Moved()),this,SLOT(in_Mouse_Moved()));
}

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
    QBarSet *set0 = new QBarSet("Probability");
    *set0 << 0.0001 << 0.0044 << 0.054 << 0.242 << 0.3989 << 0.242 << 0.054 << 0.0044 << 0.0001 << 0;
    series->append(set0);
    chart->addSeries(series);
    chart->createDefaultAxes();
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
    QImage number_image_real;
//    Mat image_pre_proess;
    number_image_real = number_image.scaled(28, 28, Qt::KeepAspectRatioByExpanding);//,Qt::SmoothTransformation);
//    image_pre_proess = QImage2cvMat(number_image_real);
//    imshow("processed",image_pre_proess);
//    std::cout<<"the number Mat is:"<<endl<<image_pre_proess<<endl<<endl;
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
         value_white = qRgb(255, 255, 255);
    plotboard->clear();
    if(ui->graphicsView->left_mouse_pressed == true)
    {
        for(int counter_x = 0; counter_x < draw_inter_factor; counter_x++)
        {
            for(int counter_y = 0; counter_y < draw_inter_factor; counter_y++)
            {
                number_image.setPixel((ui->graphicsView->left_events_buffer[0].x) + counter_x,(ui->graphicsView->left_events_buffer[0].y) + counter_y,value_blue);
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
                //number_image.setPixel((ui->graphicsView->right_events_buffer[0].x) + counter_x,(ui->graphicsView->right_events_buffer[0].y) + counter_y,value_white);
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
Function:     Mat CMOS_Camera::QImage2cvMat(QImage image)
Description:  Image2cvMat
Calls:        none
Called By:    none
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
//Mat Dialog::QImage2cvMat(QImage image)
//{
//    cv::Mat mat;
//    qDebug() << image.format();
//    switch(image.format())
//    {
//    case QImage::Format_ARGB32:
//    case QImage::Format_RGB32:
//    case QImage::Format_ARGB32_Premultiplied:
//        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
//        break;
//    case QImage::Format_RGB888:
//        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
//        break;
//    case QImage::Format_Indexed8:
//        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
//        break;
//    case QImage::Format_Grayscale8:
//        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
//        break;
//    default:
//        break;
//    }
//    return mat;
//}

/*************************************************
Function:     QImage CMOS_Camera::cvMat2QImage(const Mat &mat)
Description:  Mat2QImage
Calls:        none
Called By:    none
Input:        none
Output:       none
Return:       none
Others:       none
*************************************************/
//QImage Dialog::cvMat2QImage(const Mat &mat)
//{
//    // 8-bits unsigned, NO. OF CHANNELS = 1
//    if(mat.type() == CV_8UC1)
//    {
//        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
//        // Set the color table (used to translate colour indexes to qRgb values)
//        image.setColorCount(256);
//        for(int i = 0; i < 256; i++)
//        {
//            image.setColor(i, qRgb(i, i, i));
//        }
//        // Copy input Mat
//        uchar *pSrc = mat.data;
//        for(int row = 0; row < mat.rows; row ++)
//        {
//            uchar *pDest = image.scanLine(row);
//            memcpy(pDest, pSrc, mat.cols);
//            pSrc += mat.step;
//        }
//        return image;
//    }
//    // 8-bits unsigned, NO. OF CHANNELS = 3
//    else if(mat.type() == CV_8UC3)
//    {
//        // Copy input Mat
//        const uchar *pSrc = (const uchar*)mat.data;
//        // Create QImage with same dimensions as input Mat
//        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
//        return image.rgbSwapped();
//    }
//    else if(mat.type() == CV_8UC4)
//    {
//        qDebug() << "CV_8UC4";
//        // Copy input Mat
//        const uchar *pSrc = (const uchar*)mat.data;
//        // Create QImage with same dimensions as input Mat
//        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
//        return image.copy();
//    }
//    else
//    {
//        qDebug() << "ERROR: Mat could not be converted to QImage.";
//        return QImage();
//    }
//}

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
//    set0 = new QBarSet("Probability");
    series = new QBarSeries();
    chart = new QChart();
    X_axis = new QBarCategoryAxis();

//    *set0 << 0.0001 << 0.0044 << 0.054 << 0.242 << 0.3989 << 0.242 << 0.054 << 0.0044 << 0.0001 << 0;
//    series->append(set0);
//    chart->addSeries(series);
    chart->setTitle("Tianji computation result");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    categories << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
    X_axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(X_axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}
