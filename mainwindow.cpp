#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qtextbrowser.h"
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
    "01111111111111101111101100100001011010100000100000100000100000100000101101010100001101000100000" // 11, 5, 90
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(new QWidget, "Coded tab");
    QTextBrowser* tb = ui->tab->findChild<QTextBrowser*>("textBrowser");

    // LAYOUT SETUP
    // centralWidget
    QHBoxLayout* centralWidgetLayout = new QHBoxLayout();
    ui->centralwidget->setLayout(centralWidgetLayout);
    centralWidgetLayout->addWidget(ui->componentsList, 25);
    ui->componentsList->setMaximumWidth(175);
    centralWidgetLayout->addWidget(ui->tabWidget, 75);
    ui->tabWidget->setMinimumWidth(600);
    ui->tabWidget->setMinimumHeight(500);

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


    // MOCK DATA SETUP
    CanBus cb;
    CommunicationFrame* frames[10];
    FrameWidget* frameDisplays[10];
//    QFrame* tab_2Frame = new QFrame(ui->messageHistoryTab);
    QGridLayout* layout = new QGridLayout(ui->scrollAreaWidgetContents);
//    QGroupBox *groupBox = new QGroupBox(tr("Exclusive Radio Buttons"), ui->messageHistoryTab);

//    QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
//    QRadioButton *radio2 = new QRadioButton(tr("R&adio button 2"));
//    QRadioButton *radio3 = new QRadioButton(tr("Ra&dio button 3"));

//    radio1->setChecked(true);

//    QVBoxLayout *vbox = new QVBoxLayout;
//    vbox->addWidget(radio1);
//    vbox->addWidget(radio2);
//    vbox->addWidget(radio3);

//    ui->scrollArea->setWidgetResizable(true);
//    ui->scrollAreaWidgetContents->setMinimumSize(1000, 800);
//    ui->scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    for (int j = 1; j < 30; ++j)
    {
        int i = j % 6 + 1;
        std::bitset<FRAME_MAXIMUM_LENGTH> bs(communicationFrameStrings[i]);
        frames[i] = new CommunicationFrame(bs);
        tb->append("Identifier: ");
        tb->append(std::to_string(frames[i]->getIdentifier()).c_str());
        tb->append("Data: ");
        tb->append(std::to_string(frames[i]->getTransmittedData()).c_str());
        tb->append("Encoded message: ");
        tb->append(frames[i]->getEncodedMessage().to_string().c_str());
        tb->append("\n");

        cb.addCandidateMessage(*frames[i]);
        frameDisplays[i] = new FrameWidget(frames[i]);
//        vbox->addWidget(frameDisplays[i]);
        layout->addWidget(frameDisplays[i]);
        layout->addWidget(frameDisplays[i]);
        layout->addWidget(frameDisplays[i]);
    }

//    layout->addWidget(frameDisplays[2], 0, 0);
//    layout->addWidget(frameDisplays[3], 1, 0);
//    layout->addWidget(frameDisplays[4], 2, 0);
//    layout->addWidget(frameDisplays[1], 3, 0);


//    layout->addStretch(1);
//    ui->messageHistoryTab->setLayout(layout);
//    vbox->addStretch(1);
//    groupBox->setLayout(vbox);

    cb.advanceTransmission();


    // DEVICES SETUP
    ComponentsListItem* starter = new ComponentsListItem(16, "Dashboard");
    ui->componentListWidget->addItem(starter);
    ui->componentListWidget->addItem(new ComponentsListItem(43, "Break Sensor"));
    currentDevice = starter->getDevice();

//    std::bitset<FRAME_MAXIMUM_LENGTH> bs(communicationFrameStrings[2]);
//    new FrameDisplay(new CommunicationFrame(bs), ui->messageHistoryTab);
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
        ui->componentListWidget->addItem(
            new ComponentsListItem(
                deviceAdditionForm->getDeviceId(),
                deviceAdditionForm->getDeviceName()
            )
        );
    }
}


void MainWindow::on_RemovalButton_clicked()
{
    ComponentsListItem* selectedDevice = (ComponentsListItem*) ui->componentListWidget->currentItem();
    delete selectedDevice;
}


void MainWindow::on_ComponentList_itemClicked(QListWidgetItem *item)
{
    ComponentsListItem* selectedDeviceItem = (ComponentsListItem*) item;
    currentDevice = selectedDeviceItem->getDevice();
}

