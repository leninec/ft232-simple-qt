#include "widget.h"
#include "ui_widget.h"
#include <QDebug>


#include <Windows.h> // comes first
#include "ftd2xx.h" // comes *after* Windows.h+



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    FTDI myFtdi;

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QVector<QString> Devices;
    qDebug() << "Start function";
    int n =  myFtdi.getQuntatiDevice();
   // int n = 1;
    qDebug() << "after ftdi function";
    qDebug() << n;
    if (n == 1)
    {
        Devices = myFtdi.searthDevice();
        for (int i=0; i<Devices.size(); i++)
        {
        ui->textBrowser->append(Devices[i]);
        }
    }
    if (n >1){
        ui->textBrowser->append("You have more than 1 FTDI device!!!");
    }
    if (n == -1){
        ui->textBrowser->append("Error !!!");
    }
    if (n == 0){
        ui->textBrowser->append(" Can not find any device");
    }
}
int Widget::CloseFtdi(){
    int status;
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    ftStatus = FT_Open(0,&ftHandle);
    if (ftStatus == FT_OK)
    {  // FT_Open OK, use ftHandle to access device
        // when finished, call FT_Close
        FT_Close(ftHandle);
        ui->textBrowser->append(" FT232 close");
    }
        else {  // FT_Open failed
        status = ftStatus;
        ui->textBrowser->append(" Error");
    }


    return status;
}
int Widget::OpenFtdi(){
    int status;

    return status;
}
int Widget::ResetFtdi(){
    int status;

    return status;
}



void Widget::on_pushButton_3_clicked()
{
    ui->textBrowser->clear();
}
