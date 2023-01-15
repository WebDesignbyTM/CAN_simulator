#include "MessageHistoryView.h"
#include "ui_MessageHistoryView.h"

#include <QVBoxLayout>

MessageHistoryView::MessageHistoryView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageHistoryView)
{
    ui->setupUi(this);

    QVBoxLayout* outerLayout = new QVBoxLayout();
    setLayout(outerLayout);
    outerLayout->addWidget(ui->historyLabel);
    outerLayout->addWidget(ui->scrollArea);
}

void MessageHistoryView::setDevice(NetworkDevice *newDevice)
{
    device = newDevice;
    fetchReceivedFrames();
}

void clearLayout1(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout1(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void MessageHistoryView::fetchReceivedFrames()
{
    if (ui->scrollAreaWidgetContents->layout() == nullptr)
        ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout());
    QVBoxLayout* contentLayout = (QVBoxLayout*) ui->scrollAreaWidgetContents->layout();
    clearLayout1(contentLayout);

    if (device != nullptr)
    {
        std::vector<CommunicationFrame*> frames = device->getReceivedFrames();

        for (auto frame : frames)
            contentLayout->addWidget(new FrameWidget(frame));
    }
}

MessageHistoryView::~MessageHistoryView()
{
    delete ui;
}
