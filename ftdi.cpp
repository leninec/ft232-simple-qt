#include "ftdi.h"

FTDI::FTDI()
{
    qDebug()<<"Constructor start";
    iDev = -1; // no device
    ftHandle = 0;

}
FTDI::~FTDI()
{
    qDebug()<<"Destructor start";
    if (ftHandle != 0)
    {
        CloseFtdi(iDev);
        qDebug()<<"Destructor ftdi close";
    }
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
        /*    deviceInfo.append( "Dev________N:" + num.setNum(i).rightJustified(50,' '));
            deviceInfo.append( "Flags.......=" + flag.setNum(devInfo[i].Flags).rightJustified(50,' '));
            deviceInfo.append( "Type........=" + id.setNum(devInfo[i].Type).rightJustified(50,' '));
            deviceInfo.append( "ID          =" + flag.setNum(devInfo[i].ID).rightJustified(50,' '));
            deviceInfo.append( "LocId       =" + flag.setNum(devInfo[i].LocId).rightJustified(50,' '));
            deviceInfo.append( "SerialNumber=" + QString::fromAscii((devInfo[i].SerialNumber)).rightJustified(50,' '));
            deviceInfo.append(("Description.=" + QString::fromAscii(((devInfo[i].Description))).rightJustified(50,' ')));
*/
deviceInfo.append( num.setNum(i));
            deviceInfo.append(  flag.setNum(devInfo[i].Flags));
            deviceInfo.append(  id.setNum(devInfo[i].Type));
            deviceInfo.append(  flag.setNum(devInfo[i].ID));
            deviceInfo.append(  flag.setNum(devInfo[i].LocId));
            deviceInfo.append(  QString::fromAscii((devInfo[i].SerialNumber)));
            deviceInfo.append( QString::fromAscii(((devInfo[i].Description))));

            iDev = i;
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
/*int FTDI::getQuntatiOpenDevice()
{
   int n = mpFtDev.size();
   return n;

}
*/
int FTDI::OpenFtdi(int iDev){
    int status;
   // FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    ftStatus = FT_Open(iDev,&ftHandle);
    if (ftStatus == FT_OK)
    {  // FT_Open OK, use ftHandle to access device
        // when finished, call FT_Close

        qDebug()<<"my ftdi FT232 open";
        ftStatus = FT_SetBitMode(ftHandle, 0xff, 0x04); // all to write sync mode
        if(ftStatus != FT_OK)
        {// FT_Open failed
            qDebug()<<" Error SETUP BITMODE";
            status = ftStatus;
            return status;
        }

        ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
        if (ftStatus != FT_OK) {   // FT_SetDataCharacteristics OK
            qDebug()<<" error setup";
        }
        ftStatus = FT_SetTimeouts(ftHandle, 5000, 1000);
        if (ftStatus != FT_OK) {  // FT_SetTimeouts OK
         qDebug()<<" error timeout";
        }

        ftStatus = FT_SetBaudRate(ftHandle, 9600);
        if (ftStatus != FT_OK) {  // FT_SetTimeouts OK
         qDebug()<<" error BAUDRATE";
        }
    }     
    status = ftStatus;
    return status;
}

int FTDI::CloseFtdi(int iDev)
{
    qDebug()<<"myftdi  FT232 closing";
    int status;
    FT_STATUS ftStatus;

    ftStatus =  FT_Close(ftHandle);
    if (ftStatus == FT_OK)
    {  // FT_Open OK, use ftHandle to access device
        // when finished, call FT_Close
        qDebug()<<" FT232 close";
        iDev = -1; // no device
        ftHandle = 0;
    }
        else {  // FT_Open failed
        status = ftStatus;
        qDebug()<<" Error closing";
    }
    return status;
}
 int FTDI::SendData(int iDev, char TxBuffer, int size )
 {
     int status;
     FT_STATUS ftStatus;
     DWORD BytesWritten;
     ftStatus = FT_Write(ftHandle, &TxBuffer, sizeof(TxBuffer), &BytesWritten);
     if(ftStatus != FT_OK)
     {
         // FT_Open failed
         qDebug()<<" Error sending";
     }

//  check size TxBuffer and Byte written
     status = ftStatus;

     return status;
 }
 int FTDI::CheckOut(UCHAR &BitMode)
 {
     int status;
     FT_STATUS ftStatus;
     ftStatus = FT_GetBitMode(ftHandle, &BitMode);
     if (ftStatus == FT_OK)
     {  // BitMode contains current value
          qDebug()<<" bIT STATE";
          qDebug()<<BitMode;
     } else {
         // FT_GetBitMode FAILED!
     }
     status = ftStatus;
     return status;
 }


