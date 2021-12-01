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
    int CloseFtdi();


private:
    //FT_STATUS ftStatus;
    //DWORD numDevs;
    QMap <int, FT_HANDLE > mpFtDev;



};

#endif // FTDI_H
