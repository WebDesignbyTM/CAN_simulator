#include "FrameSetupForm.h"
#include "ui_FrameSetupForm.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

FrameSetupForm::FrameSetupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameSetupForm)
{
    ui->setupUi(this);
    QVBoxLayout* outerLayout = new QVBoxLayout();
    setLayout(outerLayout);
    outerLayout->setContentsMargins(200, 200, 200, 200);

    QHBoxLayout* dLLayout = new QHBoxLayout();
    outerLayout->addLayout(dLLayout);
    dLLayout->addWidget(ui->dLLabel, 15);
    dLLayout->addStretch(5);
    dLLayout->addWidget(ui->dLTextbox, 80);

    QHBoxLayout* dataLayout = new QHBoxLayout();
    outerLayout->addLayout(dataLayout);
    dataLayout->addWidget(ui->dataLabel, 15);
    dataLayout->addStretch(5);
    dataLayout->addWidget(ui->dataTextbox, 80);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    outerLayout->addLayout(buttonLayout);
    buttonLayout->addStretch(85);
    buttonLayout->addWidget(ui->sendButton, 15);
    ui->sendButton->setMaximumWidth(150);
}

void FrameSetupForm::setDevice(NetworkDevice* newDevice)
{
    device = newDevice;
}

void FrameSetupForm::setBus(CanBus* newBus)
{
    bus = newBus;
}

void FrameSetupForm::addListener(BusView* newListener)
{
    listener = newListener;
}

FrameSetupForm::~FrameSetupForm()
{
    delete ui;
}

void FrameSetupForm::on_sendButton_clicked()
{
    unsigned dataLength = ui->dLTextbox->text().toUInt();
    unsigned long long data = ui->dataTextbox->text().toULongLong();
    OperationDialog* operationDialog;

    if (dataLength > 0 && ui->dataTextbox->text().length() && device != nullptr)
    {
        operationDialog = new OperationDialog("Frame successfully sent for arbitration!");
        ui->dLTextbox->clear();
        ui->dataTextbox->clear();
        bus->addCandidateMessage(
            new CommunicationFrame(
                device->getId(),
                dataLength,
                data
            )
        );
        listener->fetchCandidateFrames();
    }
    else if (device == nullptr)
        operationDialog = new OperationDialog("No device is selected!");
    else
        operationDialog = new OperationDialog("Input data is not valid!");
    operationDialog->exec();
    delete operationDialog;
}

