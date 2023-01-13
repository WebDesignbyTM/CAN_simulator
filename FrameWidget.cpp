#include "FrameWidget.h"
#include "ui_FrameWidget.h"

FrameWidget::FrameWidget(CommunicationFrame* frame, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameWidget)
{
    ui->setupUi(this);
    ui->idTextbox->setText(QString::number(frame->getIdentifier()));
    ui->dLTextbox->setText(QString::number(frame->getDataLength()));
    ui->dataTextbox->setText(QString::number(frame->getTransmittedData()));
    ui->messageTextbox->setText(QString::fromStdString(frame->getEncodedMessage().to_string()));
}

FrameWidget::~FrameWidget()
{
    delete ui;
}
