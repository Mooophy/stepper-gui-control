#include "dialog.h"
#include "ui_dialog.h"
#include "Serial.hpp"
#include <string>

/**
 * @brief Ctor
 */
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

/**
 * @brief Dtor
 */
Dialog::~Dialog()
{
    delete ui;
}

/**
 * @slot startClicked
 */
void Dialog::startClicked()
{
    std::string data(4,0);
    data[0]  =  (ui->cw ->isChecked() << 4) +
                (ui->mic->isChecked() << 3) +
                (ui->hlf->isChecked() << 2) +
                (ui->ful->isChecked() << 1) +
                (ui->wav->isChecked() << 0) ;
    data[1]  =  (ui->slider_speed->value() < 75) ? (ui->slider_speed->value()) : 75;
    data[3]  =  ui->slider_steps->value();
    ui->progressBar->setValue(100);
}

/**
 * @slot speedChanged
 * @param speed
 */
void Dialog::speedChanged(int speed)
{
    ui->label_speed->setText(QString::number(speed) + "%");
}

/**
 * @slot stepsChanged
 * @param steps
 */
void Dialog::stepsChanged(int steps)
{
    ui->label_steps->setText(QString::number(steps * 10) + " steps");
}

/**
 * @slot tested
 */
void Dialog::tested()
{
    ui->progressBar->setValue(100);
}
