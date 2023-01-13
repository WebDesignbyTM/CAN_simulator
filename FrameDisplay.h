#ifndef FRAMEDISPLAY_H
#define FRAMEDISPLAY_H

#include <QFrame>
#include "CommunicationFrame.h"

namespace Ui {
class FrameDisplay;
}

class FrameDisplay : public QFrame
{
    Q_OBJECT

public:
    explicit FrameDisplay(CommunicationFrame* frame, QWidget *parent = nullptr);
    ~FrameDisplay();

private:
    Ui::FrameDisplay *ui;
};

#endif // FRAMEDISPLAY_H
