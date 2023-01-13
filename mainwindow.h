#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CommunicationFrame.h"
#include "CanBus.h"
#include "componentslistitem.h"
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

    void on_ComponentList_itemClicked(QListWidgetItem *item);

private:
    NetworkDevice* currentDevice;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
