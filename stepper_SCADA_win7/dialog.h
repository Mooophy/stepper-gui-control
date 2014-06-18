#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "qextserialport.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
void pushButtonClicked();
void serialDataReady();
void uartTest();
void speedChanged();
void stepsChanged();

private:
    Ui::Dialog *ui;
    QextSerialPort *port;
};

#endif // DIALOG_H
