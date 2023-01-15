#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <algorithm>
#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>

std::string communicationFrameStrings[] = { //
    "1111111111101110010101110111100100000100010000010100100000", // 20, 1, 1
    "00000000000000000000000000000000000000000000000011111111111111100101010011101101111101111101111101111101111101111100100001000011100000", // 97, 4, (1ULL << 32) - 1
    "11111111111111001010101011011000010000010100000110000010000010100000", // 32, 2, 1025
    "11111111111110011000111100110100010000010001000001000001110000011100000100000", // 3, 3, 1026
    "11111111111111011001001010111110100000100100000110011100000", // 102, 1, 3
    "0011111111111111101100000100000100110100100100000100001100000", // 66, 1, 44
    "01111111111111101111101100100001011010100000100000100000100000100000101101010100001101000100000" // 11, 5, 386547056730
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    busView = new BusView();
    ui->tabWidget->addTab(busView, "Information Bus");


    // LAYOUT SETUP
    // centralWidget
    QHBoxLayout* centralWidgetLayout = new QHBoxLayout();
    ui->centralwidget->setLayout(centralWidgetLayout);
    centralWidgetLayout->addWidget(ui->componentsList, 25);
    ui->componentsList->setMaximumWidth(175);
    centralWidgetLayout->addWidget(ui->tabWidget, 75);
    ui->tabWidget->setMinimumWidth(900);
    ui->tabWidget->setMinimumHeight(500);
    setMinimumWidth(1130);

    // componentsList
    QVBoxLayout* componentsListLayout = new QVBoxLayout();
    ui->componentsList->setLayout(componentsListLayout);
    componentsListLayout->addWidget(ui->componentListWidget);
    componentsListLayout->addWidget(ui->AdditionButton);
    componentsListLayout->addWidget(ui->RemovalButton);

    // messageHistoryTab
    messageHistoryView = new MessageHistoryView();
    QVBoxLayout* messageHistoryTabLayout = new QVBoxLayout();
    ui->messageHistoryTab->setLayout(messageHistoryTabLayout);
    messageHistoryTabLayout->addWidget(messageHistoryView);

    // messageSetupTab
    frameSetupForm = new FrameSetupForm();
    QVBoxLayout* messageSetupTabLayout = new QVBoxLayout();
    ui->messageSetupTab->setLayout(messageSetupTabLayout);
    messageSetupTabLayout->addWidget(frameSetupForm);


    // MOCK DATA SETUP
    canBus = new CanBus();
    frameSetupForm->setBus(canBus);
    busView->setBus(canBus);
    frameSetupForm->addListener(busView);

    // DEVICES SETUP
    ComponentsListItem* firstItem = new ComponentsListItem(16, "Dashboard");
    ComponentsListItem* secondItem = new ComponentsListItem(43, "Break Sensor");
    currentDevice = firstItem->getDevice();
    ui->componentListWidget->addItem(firstItem);
    ui->componentListWidget->addItem(secondItem);
    ui->componentListWidget->setCurrentItem(firstItem);

    canBus->subscribeDevice(firstItem->getDevice());
    canBus->subscribeDevice(secondItem->getDevice());
    messageHistoryView->setDevice(firstItem->getDevice());
    busView->addListener(messageHistoryView);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AdditionButton_clicked()
{
    DeviceAdditionForm* deviceAdditionForm = new DeviceAdditionForm();
    if (deviceAdditionForm->exec())
    {
        unsigned deviceId = deviceAdditionForm->getDeviceId();
        std::string deviceName = deviceAdditionForm->getDeviceName();
        if (0 < deviceId && deviceName.length() != 0)
            ui->componentListWidget->addItem(
                new ComponentsListItem(
                    deviceId,
                    deviceName
                )
            );
    }
    delete deviceAdditionForm;
}


void MainWindow::on_RemovalButton_clicked()
{
    ComponentsListItem* selectedDevice = (ComponentsListItem*) ui->componentListWidget->currentItem();
    if (selectedDevice != nullptr)
        canBus->unsubscribeDevice(selectedDevice->getDevice());
    delete selectedDevice;
}


void MainWindow::on_componentListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (current != nullptr)
    {
        ComponentsListItem* selectedDeviceItem = (ComponentsListItem*) current;
        currentDevice = selectedDeviceItem->getDevice();
    }
    else
        currentDevice = nullptr;
    frameSetupForm->setDevice(currentDevice);
    messageHistoryView->setDevice(currentDevice);
}

