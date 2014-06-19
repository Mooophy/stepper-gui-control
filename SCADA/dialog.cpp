#include "dialog.h"
#include "ui_dialog.h"
#include "Serial.hpp"
#include <string>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    conn("/dev/ttyUSB0",9600)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::startClicked()
{
    std::string data(4,0);

    data[0]  =  (ui->cw ->isChecked() << 4) +
                (ui->mic->isChecked() << 3) +
                (ui->hlf->isChecked() << 2) +
                (ui->ful->isChecked() << 1) +
                (ui->wav->isChecked() << 0) ;

    data[1]  = ui->slider_speed->value();
    data[3]  = ui->slider_steps->value();

    conn.writeString(data);
}

void Dialog::speedChanged(int speed)
{
    ui->label_speed->setText(QString::number(speed) + "%");
}

void Dialog::stepsChanged(int steps)
{
    ui->label_steps->setText(QString::number(steps * 10) + " steps");
}
