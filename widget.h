#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include "ftdi.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    
private slots:
    void find_Ftdi();
    void clearTextB();
  //  void openFtdi();
    void closeFtdi();
    void SetAllHi();
    void SetAllLo();

private:
    Ui::Widget *ui;
    FTDI myFtdi;
    QString readError(int);
    int iDev;
    QString description;
    QString SerialNumber;
enum
{
    CLOSE,
    OPEN,
    HI_STATE,
    LO_STATE,
};

protected:
    void paintEvent(QPaintEvent *);

};

#endif // WIDGET_H
