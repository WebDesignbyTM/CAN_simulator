#ifndef MESSAGEHISTORYVIEW_H
#define MESSAGEHISTORYVIEW_H

#include <QWidget>
#include "CommunicationFrame.h"
#include "FrameWidget.h"
#include "NetworkDevice.h"

namespace Ui {
class MessageHistoryView;
}

class MessageHistoryView : public QWidget
{
    Q_OBJECT

public:
    explicit MessageHistoryView(QWidget *parent = nullptr);
    void setDevice(NetworkDevice* newDevice);
    void fetchReceivedFrames();
    ~MessageHistoryView();

private:
    Ui::MessageHistoryView *ui;
    NetworkDevice* device;
};

#endif // MESSAGEHISTORYVIEW_H
