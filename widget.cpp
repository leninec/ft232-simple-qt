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
    FT_DEVICE_LIST_INFO_NODE *devInfo;
     QString num,flag,id,tmp2,tmp3;

    if (ftStatus == FT_OK) {

    qDebug () << numDevs;
 //   printf("Number of devices is %d \n",numDevs);
    }
    else {
    // FT_CreateDeviceInfoList failed
        ui->textBrowser->append("Fail to open device" );
    }

    if (numDevs > 0)
    {
       devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
       ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
       if (ftStatus == FT_OK) {
                      for (int i = 0; i < numDevs; i++)
                      {   ui->textBrowser->append("Dev N : " + num.setNum(i));
                          ui->textBrowser->append("Flags= " + flag.setNum(devInfo[i].Flags));
                          ui->textBrowser->append("Type= " + id.setNum(devInfo[i].Type));
                          ui->textBrowser->append("ID= " + flag.setNum(devInfo[i].ID));
                         // printf("  LocId=0x%x\n",devInfo[i].LocId);
                          ui->textBrowser->append("LocId= " + flag.setNum(devInfo[i].LocId));
                          //printf("  SerialNumber=%s\n",devInfo[i].SerialNumber);
                          ui->textBrowser->append("SerialNumber= " + QString::fromAscii((devInfo[i].SerialNumber)));
                          //printf("  Description=%s\n",devInfo[i].Description);
                          ui->textBrowser->append("Description= " + QString::fromAscii(((devInfo[i].Description))));
                          printf("  ftHandle=0x%x\n",devInfo[i].ftHandle);
                       //  ui->textBrowser->append("ftHandle= " + flag.setNum(devInfo[i].ftHandle));
                      }
       }
    }
    else{
        ui->textBrowser->append(" 0 devices found");
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
