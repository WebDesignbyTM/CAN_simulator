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

}

int DeviceAdditionForm::getDeviceId()
{
    return ui->deviceIdTextbox->text().toInt();
}

std::string DeviceAdditionForm::getDeviceName()
{
    return ui->deviceNameTextbox->text().toStdString();
}
