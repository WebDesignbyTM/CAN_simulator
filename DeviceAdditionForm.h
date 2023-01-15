#ifndef DEVICEADDITIONFORM_H
#define DEVICEADDITIONFORM_H

#include <QDialog>
#include "NetworkDevice.h"
#include "OperationDialog.h"

namespace Ui {
class DeviceAdditionForm;
}

class DeviceAdditionForm : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceAdditionForm(QWidget *parent = nullptr);
    unsigned getDeviceId();
    std::string getDeviceName();
    ~DeviceAdditionForm();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DeviceAdditionForm *ui;
};

#endif // DEVICEADDITIONFORM_H
