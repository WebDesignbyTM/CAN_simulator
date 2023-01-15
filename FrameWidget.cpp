#include "FrameWidget.h"
#include "ui_FrameWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

FrameWidget::FrameWidget(CommunicationFrame* frame, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameWidget)
{
    ui->setupUi(this);
    setMaximumHeight(200);
//    this->setMinimumHeight(140);
//    this->setMinimumWidth(850);
    ui->idTextbox->setText(QString::number(frame->getIdentifier()));
    ui->dLTextbox->setText(QString::number(frame->getDataLength()));
    ui->dataTextbox->setText(QString::number(frame->getTransmittedData()));
    ui->messageTextbox->setText(QString::fromStdString(frame->getEncodedMessage().to_string()));
//    ui->messageTextbox->setMinimumWidth(830);

    // label and textbox alignment
    ui->idLabel->setMinimumWidth(100);
    ui->idTextbox->setMinimumWidth(180);
    ui->dLLabel->setMinimumWidth(100);
    ui->dLTextbox->setMinimumWidth(180);

    // outerLayout
    QVBoxLayout* outerLayout = new QVBoxLayout();
    setLayout(outerLayout);
    outerLayout->setContentsMargins(15, 15, 15, 15);

    // idLayout
    QHBoxLayout* idLayout = new QHBoxLayout();
    outerLayout->addLayout(idLayout);
    idLayout->addWidget(ui->idLabel, 10);
    idLayout->addWidget(ui->idTextbox, 20);
    idLayout->addStretch(70);

    // dataLayout
    QHBoxLayout* dataLayout = new QHBoxLayout();
    outerLayout->addLayout(dataLayout);
    dataLayout->addWidget(ui->dLLabel, 10);
    dataLayout->addWidget(ui->dLTextbox, 20);
    dataLayout->addStretch(40);
    dataLayout->addWidget(ui->dataLabel, 10);
    dataLayout->addWidget(ui->dataTextbox, 20);

    // messageLayout
    QVBoxLayout* messageLayout = new QVBoxLayout();
    outerLayout->addLayout(messageLayout);
    messageLayout->addWidget(ui->messageLabel);
    messageLayout->addWidget(ui->messageTextbox);
}

FrameWidget::~FrameWidget()
{
    delete ui;
}
