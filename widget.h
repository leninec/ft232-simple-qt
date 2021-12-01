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
    void openFtdi();

private:
    Ui::Widget *ui;
    FTDI myFtdi;
    QString readError(int);
protected:
    void paintEvent(QPaintEvent *);

};

#endif // WIDGET_H
