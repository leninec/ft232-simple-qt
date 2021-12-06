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
    this->setFixedSize(QSize(483, 423));
    iDev= 0;


    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(find_Ftdi()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearTextB()));

    connect(ui->SEThButton, SIGNAL(clicked()), this, SLOT(SetAllHi()));
    connect(ui->SETlButton, SIGNAL(clicked()), this, SLOT(SetAllLo()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeFtdi()));

 /*   QPainter painter1; //создание рисовальщика
    painter1.begin(this); //захват контекста
    painter1.fillRect(0,0,width(),height(),Qt::CrossPattern); //отрисовка
    painter1.end();//освобождение контекста
*/
   // FTDI myFtdi;
    setWindowTitle(tr("FT232 test program"));
    ui->textBrowser->append("Start");

    ui->closeButton->hide();
    ui->SEThButton->hide();
    ui->SETlButton->hide();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::find_Ftdi()
{
    qDebug()<<"open func in widget";
    QString sEr;
    QVector<QString> Devices;
    ui->textBrowser->clear();
    int n =  this->myFtdi.getQuntatiDevice();
    if (n == 1)
    {
        Devices = this->myFtdi.searthDevice();
        for (int i=0; i<Devices.size(); i++)
        {
            ui->textBrowser->append(Devices[i]);
            /*    deviceInfo.append( "Dev________N:" + num.setNum(i).rightJustified(50,' '));
                deviceInfo.append( "Flags.......=" + flag.setNum(devInfo[i].Flags).rightJustified(50,' '));
                deviceInfo.append( "Type........=" + id.setNum(devInfo[i].Type).rightJustified(50,' '));
                deviceInfo.append( "ID          =" + flag.setNum(devInfo[i].ID).rightJustified(50,' '));
                deviceInfo.append( "LocId       =" + flag.setNum(devInfo[i].LocId).rightJustified(50,' '));
                deviceInfo.append( "SerialNumber=" + QString::fromAscii((devInfo[i].SerialNumber)).rightJustified(50,' '));
                deviceInfo.append(("Description.=" + QString::fromAscii(((devInfo[i].Description))).rightJustified(50,' ')));
    */

        }
        description  = Devices[6];
        SerialNumber = Devices[5];

        int er = myFtdi.OpenFtdi();

        if (er == 0){
            ui->textBrowser->append(" device open!!!");
            ui->SEThButton->show();
            ui->SETlButton->show();
            ui->closeButton->show();
            iDev=1;
            repaint();
        }
        else {
            ui->textBrowser->append("Error !!! "+ readError(er));
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

void Widget::closeFtdi()
{
    QString sEr;
    qDebug()<<"widget close";
    int er = myFtdi.CloseFtdi();

    if (er == 0){
        ui->textBrowser->append(" device close!!!");
        iDev=1;
        repaint();
    }
    else {
        ui->textBrowser->append("Error !!! "+ readError(er));
    }
}

void Widget::clearTextB()
{
    ui->textBrowser->clear();
}

void Widget::paintEvent(QPaintEvent *event) {
    if (iDev){
    QPainter painter(this); //новый объект "рисовальщика"
    painter.setPen (QPen(Qt::red,Qt::SolidLine));
    //создать и установить перо - красная сплошная линия
   // painter.drawLine(0,0,width(),height());
    //нарисовать линию через рабочую область формы
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
  //создать и установить кисть - зелёная слошная заливка
  //  QPoint center(width()/2,height()/2);
  //  int rad = qMin(width()/4,height()/4);
  //  painter.drawRect(10.0, 20.0, 80.0, 60.0);
  //нарисовать окружность по центру
    painter.setFont(QFont("sans-serif",-1,10));
  //установить шрифт заданного начертания и размера 10 пт
    QRect rect(50,70,241,100);
    painter.drawRect(rect);
    QString tmp = description + "\n " + SerialNumber;
    painter.drawText(rect, Qt::AlignCenter, tmp);

    QPen pen;  // перо по умолчанию
    pen.setWidth(8); // толщина пера
    pen.setBrush(Qt::red); // цвет пера
    painter.setPen(pen);

    painter.drawPoint(QPoint(270, 90));
 }
  //вывели строку текста, выравненную по центру
}
void Widget::SetAllHi()
{
    UCHAR BitMode;
    qDebug()<<"widget hi";
    char data[8] = {0xff};
    int er = myFtdi.SendData(0, data[0], 8);

    if (er == 0){
        ui->textBrowser->append(" data send!!!");
    }
    else {
        ui->textBrowser->append("Error !!! "+ readError(er));
    }
  //  er = myFtdi.CheckOut(BitMode);
  //  ui->textBrowser->append("- "+ readError(er));

}

void Widget::SetAllLo()
{
     UCHAR BitMode;
     qDebug()<<"widget lo";
     char data[8] = {0x00};
     int er = myFtdi.SendData(0, data[0], 8);

     if (er == 0){
         ui->textBrowser->append(" data send!!!");
     }
     else {
         ui->textBrowser->append("Error !!! "+ readError(er));
     }
    // er = myFtdi.CheckOut(BitMode);
    // ui->textBrowser->append("- "+ readError(er));
}

QString Widget::readError(int error){
    QString str;
    switch (error){
    case 0:
        str = " Status OK";
        break;
    case 1:
        str = "INVALID HANDLER";
        break;
    case 2:
        str = "DEVICE NOT FOUND";
        break;
    case 3:
        str = "DEVICE NOT OPENED";
        break;
    case 4:
        str = "IO ERROR";
        break;
    case 5:
        str = "INSUFFICIENT RESOURCES";
        break;
    case 6:
        str = "INVALID PARAMETER";
        break;
    case 7:
        str = "INVALID BAUD RATE";
        break;
    case 8:
        str = "DEVICE NOT OPENED FOR ERASE";
        break;
    case 9:
        str = "DEVICE NOT OPENED FOR WRITE";
        break;
    case 10:
        str = "FAILED TO WRITE DEVICE";
        break;
    case 11:
        str = "EEPROM READ FAILED";
        break;
    case 12:
        str = "EEPROM ERASE FAILED";
        break;
    case 13:
        str = "EEPROM NOT PRESENT";
        break;
    case 14:
        str = "EEPROM NOT PROGRAMMED";
        break;
    case 15:
        str = "INVALID ARGS";
        break;
    case 16:
        str = "NOT SUPPORTED";
        break;
    case 17:
        str = "OTHER ERROR";
        break;
    case 18:
        str = "DEVICE LIST NOT READY";
        break;
    default:
        str = "UNKNOWN";

    }
    return str;
}
