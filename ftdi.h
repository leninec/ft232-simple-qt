#ifndef FTDI_H
#define FTDI_H

#include <Windows.h> // comes first
#include "ftd2xx.h" // comes *after* Windows.h+

#include <QStringList>
#include <QDebug>
#include <QVector>
#include <QMap>



class FTDI
{

public:
    FTDI();
    ~FTDI();
    QVector<QString> searthDevice();
    unsigned long getQuntatiDevice();
    int OpenFtdi(int iDev = 0);
    int CloseFtdi(int i = 0);
    int SendData(int iDev, char TxBuffer[256], DWORD BytesWritten );
    int CheckOut(UCHAR &BitMode);
   // int getQuntatiOpenDevice();

private:
    //FT_STATUS ftStatus;
    //DWORD numDevs;
   // QMap <int, FT_HANDLE > mpFtDev;
    int iDev; //Index of the device to open.  Indices are 0 based
    FT_HANDLE ftHandle;  // Pointer to a variable of type FT_HANDLE where the handle will be      stored.  This handle must be used to access the device.

};

#endif // FTDI_H
