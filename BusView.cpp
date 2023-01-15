#include "BusView.h"
#include "ui_BusView.h"
#include <QHBoxLayout>

BusView::BusView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BusView)
{
    ui->setupUi(this);

    QVBoxLayout* outerLayout = new QVBoxLayout();
    setLayout(outerLayout);
    outerLayout->addWidget(ui->candFramesLabel);
    outerLayout->addWidget(ui->scrollArea);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    outerLayout->addLayout(buttonLayout);
    buttonLayout->addStretch(85);
    buttonLayout->addWidget(ui->transmitButton, 15);
}

void BusView::setBus(CanBus *newBus)
{
    bus = newBus;
}

void clearLayout2(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout2(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void BusView::fetchCandidateFrames()
{
    if (ui->scrollAreaWidgetContents->layout() == nullptr)
        ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout());

    std::vector<CommunicationFrame*> frames = bus->getCandidateFrames();

    QVBoxLayout* contentLayout = (QVBoxLayout*) ui->scrollAreaWidgetContents->layout();
    clearLayout2(contentLayout);

    for (auto frame : frames)
        contentLayout->addWidget(new FrameWidget(frame));
}

void BusView::addListener(MessageHistoryView *newListener)
{
    listener = newListener;
}

BusView::~BusView()
{
    delete ui;
}

void BusView::on_transmitButton_clicked()
{
    bus->transmitFrame();
    fetchCandidateFrames();
    if (listener != nullptr)
        listener->fetchReceivedFrames();
}

