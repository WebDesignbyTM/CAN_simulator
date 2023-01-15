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
    ui->tabWidget->addTab(new QWidget, "Coded tab");


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
    QVBoxLayout* messageHistoryTabLayout = new QVBoxLayout();
    ui->messageHistoryTab->setLayout(messageHistoryTabLayout);
    messageHistoryTabLayout->addWidget(ui->scrollArea);

    // messageSetupTab
    frameSetupForm = new FrameSetupForm();
    QVBoxLayout* messageSetupTabLayout = new QVBoxLayout();
    ui->messageSetupTab->setLayout(messageSetupTabLayout);
    messageSetupTabLayout->addWidget(frameSetupForm);


    // MOCK DATA SETUP
    CanBus cb;
    CommunicationFrame* frames[10];
    FrameWidget* frameDisplays[10];
    QGridLayout* layout = new QGridLayout(ui->scrollAreaWidgetContents);

    for (int j = 0; j < 30; ++j)
    {
        int i = j % 7;
        std::bitset<FRAME_MAXIMUM_LENGTH> bs(communicationFrameStrings[i]);
        frames[i] = new CommunicationFrame(bs);

        cb.addCandidateMessage(*frames[i]);
        frameDisplays[i] = new FrameWidget(frames[i]);
        layout->addWidget(frameDisplays[i]);
        layout->addWidget(frameDisplays[i]);
        layout->addWidget(frameDisplays[i]);
    }
//    layout->addWidget(frameDisplays[0]);

    cb.advanceTransmission();


    // DEVICES SETUP
    ComponentsListItem* starter = new ComponentsListItem(16, "Dashboard");
    currentDevice = starter->getDevice();
    ui->componentListWidget->addItem(starter);
    ui->componentListWidget->addItem(new ComponentsListItem(43, "Break Sensor"));
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
    delete selectedDevice;
}


void MainWindow::on_componentListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ComponentsListItem* selectedDeviceItem = (ComponentsListItem*) current;
    currentDevice = selectedDeviceItem->getDevice();
    frameSetupForm->setDevice(currentDevice);
    // update all components that depend on the currentDevice
//    std::cout << currentDevice->getName() << '\n';
}

