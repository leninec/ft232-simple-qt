#include "ftdi.h"

FTDI::FTDI()
{
    qDebug()<<"Constructor start";

}
FTDI::~FTDI()
{
    qDebug()<<"Destructor start";
}

QVector<QString> FTDI::searthDevice()
{
    QVector<QString> deviceInfo;
    FT_STATUS ftStatus;
    unsigned long numDevs;
    FT_HANDLE ftHandle;
    // create the device information list
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    FT_DEVICE_LIST_INFO_NODE *devInfo;
    QString num,flag,id,tmp2,tmp3;

    if (numDevs > 0)
    {
       devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
       ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
       if (ftStatus == FT_OK)
       {
        for (int i = 0; i < numDevs; i++)
         {

                deviceInfo.append( "Dev N : " + num.setNum(i));
                deviceInfo.append("Flags= " + flag.setNum(devInfo[i].Flags));
                deviceInfo.append("Type= " + id.setNum(devInfo[i].Type));
                deviceInfo.append("ID= " + flag.setNum(devInfo[i].ID));
                deviceInfo.append("LocId= " + flag.setNum(devInfo[i].LocId));
                deviceInfo.append("SerialNumber= " + QString::fromAscii((devInfo[i].SerialNumber)));
                deviceInfo.append(("Description= " + QString::fromAscii(((devInfo[i].Description)))));
                mpFtDev.insert(i,  ftHandle);
          }
         }
    }

    else{
        deviceInfo.append( "0 devices found ") ;

    }
    return deviceInfo;
}
unsigned long FTDI::getQuntatiDevice()
{
    FT_STATUS ftStatus;
    unsigned long numDevs;
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if (ftStatus == FT_OK)
    {

        //qDebug() << numDevs;
        return numDevs;
    }
    else {
        return -1;
    }
}
int FTDI::getQuntatiOpenDevice()
{
   int n = mpFtDev.size();
   return n;

}
int FTDI::OpenFtdi(int iDev){
    int status;
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    ftStatus = FT_Open(iDev,&ftHandle);
    if (ftStatus == FT_OK)
    {  // FT_Open OK, use ftHandle to access device
        // when finished, call FT_Close

        qDebug()<<" FT232 open";
        mpFtDev[iDev] = ftHandle;
    }
        else {  // FT_Open failed
        status = ftStatus;
        qDebug()<<" Error closing";
    }
    return status;
}

int FTDI::CloseFtdi(int iDev){
    int status;
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    ftStatus = FT_Open(iDev,&ftHandle);
    if (ftStatus == FT_OK)
    {  // FT_Open OK, use ftHandle to access device
        // when finished, call FT_Close
        FT_Close(ftHandle);
        qDebug()<<" FT232 close";
    }
        else {  // FT_Open failed
        status = ftStatus;
        qDebug()<<" Error closing";
    }
    return status;
}
int FTDI::CloseFtdi(){
    int status;
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    for (int n =0; n<mpFtDev.size(); n++)
    {


      ftStatus =  FT_Close(mpFtDev[n]);
      if(ftStatus == FT_OK){
       qDebug()<<" FT232 close";
      }
        else {  // FT_Open failed

        qDebug()<<" Error closing";
       }
    }
    return status;
}

