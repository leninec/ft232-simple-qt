#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <Windows.h> // comes first
#include "ftd2xx.h" // comes *after* Windows.h



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    FT_STATUS ftStatus;
    unsigned long numDevs;
    // create the device information list
    ftStatus = FT_CreateDeviceInfoList(&numDevs);

    if (ftStatus == FT_OK) {

    qDebug () << numDevs;
 //   printf("Number of devices is %d \n",numDevs);
    }
    else {
    // FT_CreateDeviceInfoList failed
    }

}
