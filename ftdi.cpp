#include "ftdi.h"

FTDI::FTDI()
{


}
QVector<QString> FTDI::searthDevice(int i)
{
    QVector<QString> deviceList;
    FT_STATUS ftStatus;
    unsigned long numDevs;
    // create the device information list
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    FT_DEVICE_LIST_INFO_NODE *devInfo;
    QString num,flag,id,tmp2,tmp3;

    if (numDevs >= i)
    {
       devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
       ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
       if (ftStatus == FT_OK)
       {
                deviceList.append( "Dev N : " + num.setNum(i));
                deviceList.append("Flags= " + flag.setNum(devInfo[i].Flags));
                deviceList.append("Type= " + id.setNum(devInfo[i].Type));
                deviceList.append("ID= " + flag.setNum(devInfo[i].ID));
                deviceList.append("LocId= " + flag.setNum(devInfo[i].LocId));
                deviceList.append("SerialNumber= " + QString::fromAscii((devInfo[i].SerialNumber)));
                deviceList.append(("Description= " + QString::fromAscii(((devInfo[i].Description)))));

       }
    }

    else{
        deviceList.append( "0 devices found ") ;

    }
    return deviceList;
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

