#include "DeviceAdditionForm.h"
#include "ui_DeviceAdditionForm.h"

DeviceAdditionForm::DeviceAdditionForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceAdditionForm)
{
    ui->setupUi(this);
}

DeviceAdditionForm::~DeviceAdditionForm()
{
    delete ui;
}

void DeviceAdditionForm::on_buttonBox_accepted()
{
    if (getDeviceId() && getDeviceName().length())
    {
        OperationDialog* operationDialog = new OperationDialog("Device successfully added!");
        operationDialog->exec();
        delete operationDialog;
    }
}

unsigned DeviceAdditionForm::getDeviceId()
{
    return ui->deviceIdTextbox->text().toUInt();
}

std::string DeviceAdditionForm::getDeviceName()
{
    return ui->deviceNameTextbox->text().toStdString();
}
