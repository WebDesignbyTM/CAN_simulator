#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qtextbrowser.h"
#include <algorithm>
#include <iostream>

std::string communicationFrameStrings[] = { //
    "0000010010100000100010000010011110111010100111011111111111", // 20, 1, 1; reverse this
    "00000000000000000000000000000000000000000000000011111111111111100101010011101101111101111101111101111101111101111100100001000011100000", // 97, 4, (1ULL << 32) - 1
    "11111111111111001010101011011000010000010100000110000010000010100000", // 32, 2, 1025
    "11111111111110011000111100110100010000010001000001000001110000011100000100000", // 3, 3, 1026
    "11111111111111011001001010111110100000100100000110011100000", // 102, 1, 3
    "0011111111111111101100000100000100110100100100000100001100000", // 66, 1, 44
    "01111111111111101111101100100001011010100000100000100000100000100000101101010100001101000100000" // 11, 5, 90
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(new QWidget, "Coded tab");
    QTextBrowser* tb = ui->tab->findChild<QTextBrowser*>("textBrowser");

    CanBus cb;

    for (int i = 1; i < 7; ++i)
    {
        std::bitset<FRAME_MAXIMUM_LENGTH> bs(communicationFrameStrings[i]);
        CommunicationFrame cf(bs);
        tb->append("Identifier: ");
        tb->append(std::to_string(cf.getIdentifier()).c_str());
        tb->append("Data: ");
        tb->append(std::to_string(cf.getTransmittedData()).c_str());
        tb->append("Encoded message: ");
        tb->append(cf.getEncodedMessage().to_string().c_str());
        tb->append("\n");

        cb.addCandidateMessage(cf);
    }

    cb.advanceTransmission();


    // DEVICES SETUP
    ComponentsListItem* starter = new ComponentsListItem(16, "Dashboard");
    ui->ComponentList->addItem(starter);
    ui->ComponentList->addItem(new ComponentsListItem(43, "Break Sensor"));
    currentDevice = starter->getDevice();
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
        ui->ComponentList->addItem(
            new ComponentsListItem(
                deviceAdditionForm->getDeviceId(),
                deviceAdditionForm->getDeviceName()
            )
        );
    }
}


void MainWindow::on_RemovalButton_clicked()
{
    ComponentsListItem* selectedDevice = (ComponentsListItem*) ui->ComponentList->currentItem();
    delete selectedDevice;
}


void MainWindow::on_ComponentList_itemClicked(QListWidgetItem *item)
{
    ComponentsListItem* selectedDeviceItem = (ComponentsListItem*) item;
    currentDevice = selectedDeviceItem->getDevice();
}

