#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CommunicationFrame.h"
#include "CanBus.h"
#include "componentslistitem.h"
#include "DeviceAdditionForm.h"
#include "FrameWidget.h"
#include "FrameSetupForm.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AdditionButton_clicked();

    void on_RemovalButton_clicked();

    void on_componentListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    CanBus canBus;
    NetworkDevice* currentDevice;
    FrameSetupForm* frameSetupForm;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
