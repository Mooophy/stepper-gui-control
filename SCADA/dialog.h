#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "Serial.hpp"

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
    void startClicked();
    void speedChanged(int speed);
    void stepsChanged(int steps);
    void tested();

private:
    Ui::Dialog *ui;
    //SimpleSerial conn;
};

#endif // DIALOG_H
