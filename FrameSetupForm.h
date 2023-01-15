#ifndef FRAMESETUPFORM_H
#define FRAMESETUPFORM_H

#include <QWidget>
#include "NetworkDevice.h"
#include "CommunicationFrame.h"
#include "OperationDialog.h"
#include "CanBus.h"
#include "BusView.h"

namespace Ui {
class FrameSetupForm;
}

class FrameSetupForm : public QWidget
{
    Q_OBJECT

public:
    explicit FrameSetupForm(QWidget *parent = nullptr);
    void setDevice(NetworkDevice* newDevice);
    void setBus(CanBus* bus);
    void addListener(BusView* newListener);
    ~FrameSetupForm();

private slots:
    void on_sendButton_clicked();

private:
    Ui::FrameSetupForm *ui;
    NetworkDevice* device;
    CanBus* bus;
    BusView* listener;
};

#endif // FRAMESETUPFORM_H
