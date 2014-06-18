#include "dialog.h"
#include "ui_dialog.h"
#include <string>

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

Dialog::~Dialog()
{
    delete ui;
    delete port;
}

void Dialog::pushButtonClicked(void)
{
    /**
     * @brief command encoding
     *
     *  check the protocol file for detail
     */
    QByteArray cmd(4,0);

    //! mode and direction
    cmd[0]  = 0x18;

    //! speed:  [2,100]
    cmd[1]  = 80;

    //! steps:  [0,100] and [1,100]
    cmd[2]  = 0;
    cmd[3]  = 50;

    port->write(cmd);
}

void Dialog::serialDataReady()
{
    if (port->canReadLine()) {
        char s[80];
        port->readLine(s, 80);
        s[strlen(s)-1] = '\0';
        ui->label->setText(s);
    }
}

