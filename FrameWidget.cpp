#include "FrameWidget.h"
#include "ui_FrameWidget.h"

FrameWidget::FrameWidget(CommunicationFrame* frame, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameWidget)
{
    ui->setupUi(this);
    this->setMinimumHeight(140);
    this->setMinimumWidth(850);
    ui->idTextbox->setText(QString::number(frame->getIdentifier()));
    ui->dLTextbox->setText(QString::number(frame->getDataLength()));
    ui->dataTextbox->setText(QString::number(frame->getTransmittedData()));
    ui->messageTextbox->setText(QString::fromStdString(frame->getEncodedMessage().to_string()));
    ui->messageTextbox->setMinimumWidth(830);
}

FrameWidget::~FrameWidget()
{
    delete ui;
}
