#include "dialog.h"
#include "ui_dialog.h"
#include <string>

/**
 * @brief ctor
 */
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    PortSettings settings = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    port = new QextSerialPort("COM3", settings, QextSerialPort::EventDriven);
    connect(port, SIGNAL(readyRead()), SLOT(serialDataReady()));
    port->open(QIODevice::ReadWrite);

}

/**
 * @brief dtor
 */
Dialog::~Dialog()
{
    delete ui;
    delete port;
}

/**
 * @brief pushButtonClicked
 *
 * slot for command sending
 */
void Dialog::pushButtonClicked(void)
{
    /**
     * @brief command encoding
     *
     *  check the protocol file for detail
     */
    QByteArray cmd(4,0);

    bool wave   =   ui->radioButton_wave->isChecked();
    bool full   =   ui->radioButton_full->isChecked();
    bool half   =   ui->radioButton_half->isChecked();
    bool mirc   =   ui->radioButton_micr->isChecked();

    bool cw     =   ui->radioButton_cw->isChecked();

    //! mode and direction
    //cmd[0]  = 0x11;
    cmd[0]  = (cw<<4) + (mirc<<3) + (half<<2) + (full<<1) + (wave<<0);

    //! speed:  [2,100]
    cmd[1]  = ui->slider_speed->value();

    //! steps:  [0,100] and [1,100]
    cmd[2]  = ui->slider_steps->value() >> 8;
    cmd[3]  = ui->slider_steps->value() >> 0;


    port->write(cmd);
}

/**
 * @brief serialDataReady
 *
 * slot when data is being receiving
 */
void Dialog::serialDataReady()
{
    if (port->canReadLine()) {
        char s[80];
        port->readLine(s, 80);
        s[strlen(s)-1] = '\0';

        if(strlen(s) > 0)
        {
            ui->label->setText("Uart State : Working!");
        }
    }
}

/**
 * @brief uartTest
 *
 * slot for uart test
 */
void Dialog::uartTest()
{
    QByteArray test(1,'C');
    port->write(test);
}

void Dialog::speedChanged()
{
    QString speed = QString::number(ui->slider_speed->value());
    speed += "%";
    ui->label_speed->setText(speed);
}

/**
 * @brief Dialog::stepsChanged
 */
void Dialog::stepsChanged()
{
    QString steps = QString::number(ui->slider_steps->value());
    steps += " steps";
    ui->label_steps->setText(steps);
}

