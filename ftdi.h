#ifndef FTDI_H
#define FTDI_H

#include <Windows.h> // comes first
#include "ftd2xx.h" // comes *after* Windows.h+

#include <QStringList>
#include <QDebug>
#include <QVector>



class FTDI
{
public:
    FTDI();
    QVector<QString> searthDevice(int i =0);
    unsigned long getQuntatiDevice();


private:
    //FT_STATUS ftStatus;
    //DWORD numDevs;


};

#endif // FTDI_H
