#ifndef BUSVIEW_H
#define BUSVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include "CanBus.h"
#include "CommunicationFrame.h"
#include "FrameWidget.h"
#include "MessageHistoryView.h"

namespace Ui {
class BusView;
}

class BusView : public QWidget
{
    Q_OBJECT

public:
    explicit BusView(QWidget *parent = nullptr);
    void setBus(CanBus* newBus);
    void fetchCandidateFrames();
    void addListener(MessageHistoryView* newListener);
    ~BusView();

private slots:
    void on_transmitButton_clicked();

private:
    Ui::BusView *ui;
    CanBus* bus;
    MessageHistoryView* listener;
};

#endif // BUSVIEW_H
