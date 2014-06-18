#include "dialog.h"
#include "ui_dialog.h"

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

void Dialog::pushButtonClicked(void) {
    QByteArray qba = (ui->lineEdit->text() + '\n').toLatin1();
    port->write(qba.data());
}

void Dialog::serialDataReady() {
    if (port->canReadLine()) {
        char s[80];
        port->readLine(s, 80);
        s[strlen(s)-1] = '\0';
        ui->label->setText(s);
    }
}

