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

#define inter_factor 25

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    plotboard  = new QGraphicsScene(this);
    ui->graphicsView->setScene(plotboard);
    plotboard->clear();
    number_image.fill(Qt::white);
    plotboard->addPixmap(QPixmap::fromImage(number_image));

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
    Mat image_pre_proess;
    number_image_real = number_image.scaled(28, 28, Qt::KeepAspectRatioByExpanding);//,Qt::SmoothTransformation);
    image_pre_proess = QImage2cvMat(number_image_real);
    imshow("processed",image_pre_proess);
//    for(int counter_y = 0; counter_y < number_image_real.bytesPerLine(); counter_y++)
//    {
//        for(int counter_x = 0; counter_x < number_image_real.bytesPerLine(); counter_x++)
//        {
//            qDebug() << image_pionter;
//            image_pionter++;
//        }
//        qDebug()<<endl;
//    }
    std::cout<<"the number Mat is:"<<endl<<image_pre_proess<<endl<<endl;
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
void Dialog::on_stop_clicked()
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
    plotboard->clear();
    for(int counter_x = 0; counter_x < inter_factor; counter_x++)
    {
        for(int counter_y = 0; counter_y < inter_factor; counter_y++)
        {
            number_image.setPixel((ui->graphicsView->events_buffer[0].x) + counter_x,(ui->graphicsView->events_buffer[0].y) + counter_y,Qt::black);
        }
    }
    ui->graphicsView->events_buffer.clear();
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
Mat Dialog::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_Grayscale8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    default:
        break;
    }
    return mat;
}

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
QImage Dialog::cvMat2QImage(const Mat &mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}
