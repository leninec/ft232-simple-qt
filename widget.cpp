#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPainter>



#include <Windows.h> // comes first
#include "ftd2xx.h" // comes *after* Windows.h+



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   // this->setFixedSize(QSize(483, 564));

    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(find_Ftdi()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearTextB()));


    QPainter painter1; //�������� ������������
    painter1.begin(this); //������ ���������
    painter1.fillRect(0,0,width(),height(),Qt::CrossPattern); //���������
    painter1.end();//������������ ���������


    FTDI myFtdi;
    setWindowTitle(tr("FT232 test program"));
    ui->textBrowser->append("Start");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::find_Ftdi()
{
    qDebug()<<"open func in widget";
    QVector<QString> Devices;
    ui->textBrowser->clear();
    int n =  this->myFtdi.getQuntatiDevice();
    if (n == 1)
    {
        Devices = this->myFtdi.searthDevice();
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




void Widget::clearTextB()
{
    ui->textBrowser->clear();
     qDebug()<<"clear";
}
