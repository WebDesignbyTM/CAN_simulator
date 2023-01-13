#include "FrameDisplay.h"
#include "ui_FrameDisplay.h"

FrameDisplay::FrameDisplay(CommunicationFrame* frame, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameDisplay)
{
    ui->setupUi(this);
    ui->idTextbox->setText(QString::number(frame->getIdentifier()));
    ui->dLTextbox->setText(QString::number(frame->getDataLength()));
    ui->dataTextbox->setText(QString::number(frame->getTransmittedData()));
    ui->messageTextbox->setText(QString::fromStdString(frame->getEncodedMessage().to_string()));
}

FrameDisplay::~FrameDisplay()
{
    delete ui;
}
