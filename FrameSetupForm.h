#ifndef FRAMESETUPFORM_H
#define FRAMESETUPFORM_H

#include <QWidget>
#include "NetworkDevice.h"
#include "CommunicationFrame.h"
#include "OperationDialog.h"

namespace Ui {
class FrameSetupForm;
}

class FrameSetupForm : public QWidget
{
    Q_OBJECT

public:
    explicit FrameSetupForm(QWidget *parent = nullptr);
    void setDevice(NetworkDevice* newDevice);
    ~FrameSetupForm();

private slots:
    void on_sendButton_clicked();

private:
    Ui::FrameSetupForm *ui;
    NetworkDevice* device;
};

#endif // FRAMESETUPFORM_H
