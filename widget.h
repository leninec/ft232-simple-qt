#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
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

private:
    Ui::Widget *ui;
    FTDI myFtdi;

};

#endif // WIDGET_H
