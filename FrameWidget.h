#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>
#include "CommunicationFrame.h"

namespace Ui {
class FrameWidget;
}

class FrameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FrameWidget(CommunicationFrame* frame, QWidget *parent = nullptr);
    ~FrameWidget();

private:
    Ui::FrameWidget *ui;
};

#endif // FRAMEWIDGET_H
