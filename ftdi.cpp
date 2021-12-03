#include "ftdi.h"

FTDI::FTDI()
{
    qDebug()<<"Constructor start";
    iDev = -1; // no device

}
FTDI::~FTDI()
{
    qDebug()<<"Destructor start";
    if (iDev != -1)
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

            deviceInfo.append( "Dev________N:" + num.setNum(i).rightJustified(50,' '));
            deviceInfo.append( "Flags.......=" + flag.setNum(devInfo[i].Flags).rightJustified(50,' '));
            deviceInfo.append( "Type........=" + id.setNum(devInfo[i].Type).rightJustified(50,' '));
            deviceInfo.append( "ID          =" + flag.setNum(devInfo[i].ID).rightJustified(50,' '));
            deviceInfo.append( "LocId       =" + flag.setNum(devInfo[i].LocId).rightJustified(50,' '));
            deviceInfo.append( "SerialNumber=" + QString::fromAscii((devInfo[i].SerialNumber)).rightJustified(50,' '));
            deviceInfo.append(("Description.=" + QString::fromAscii(((devInfo[i].Description))).rightJustified(50,' ')));
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

        qDebug()<<" FT232 open";
        FT_SetBitMode(ftHandle, 0xff, 0x04); // all to write sync mode
        ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
        if (ftStatus == FT_OK) {   // FT_SetDataCharacteristics OK
        }  else {
             qDebug()<<" error setup";

        }
        ftStatus = FT_SetTimeouts(ftHandle, 5000, 1000);
        if (ftStatus == FT_OK) {  // FT_SetTimeouts OK
        }
            else {  // FT_SetTimeouts failed
            }
        ftStatus = FT_SetBaudRate(ftHandle, 9600);

    }
        else {  // FT_Open failed

        qDebug()<<" Error closing";
    }
    status = ftStatus;
    return status;
}

int FTDI::CloseFtdi(int iDev)
{
    qDebug()<<"myftdi  FT232 closing";
    int status;
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
 int FTDI::SendData(int iDev, char TxBuffer[256] )
 {
     int status;
     FT_STATUS ftStatus;
     DWORD BytesWritten;
     ftStatus = FT_Open(iDev, &ftHandle);
     if(ftStatus != FT_OK)
     {
         // FT_Open failed
         status = ftStatus;
         return status;
     }
     ftStatus = FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);
//  check size TxBuffer and Byte written
     status = ftStatus;

     return status;
 }
 int FTDI::CheckOut(UCHAR &BitMode)
 {
     int status;
     FT_STATUS ftStatus;
     ftStatus = FT_Open(iDev, &ftHandle);
     if(ftStatus != FT_OK)
     {
         // FT_Open failed
         status = ftStatus;
         return status;
     }
     ftStatus = FT_GetBitMode(ftHandle, &BitMode);
     if (ftStatus == FT_OK)
     {  // BitMode contains current value
     } else {
         // FT_GetBitMode FAILED!
     }
     status = ftStatus;
     return status;
 }


