#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qtextbrowser.h"
#include "CommunicationFrame.h"
#include <algorithm>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("Coded component");
    ui->tabWidget->addTab(new QWidget, "Coded tab");
    QTextBrowser* tb = ui->tab->findChild<QTextBrowser*>("textBrowser");
    std::string s = "000001001010000010001000001001"    // initial part of the message
                    "111011101010011"                   // the crc (which i had to recompute by hand)
                    "1011111111111";                    // final frame bits
    std::reverse(s.begin(), s.end());
    std::bitset<FRAME_MAXIMUM_LENGTH> bs(s);
//    std::cout << bs << '\n';
    CommunicationFrame cf(bs);
//    std::cout << cf.getEncodedMessage().to_string() << '\n';
    tb->append("Identifier: ");
    tb->append(std::to_string(cf.getIdentifier()).c_str());
    tb->append("\nData: ");
    tb->append(std::to_string(cf.getTransmittedData()).c_str());
    tb->append("\nEncoded message: ");
    tb->append(cf.getEncodedMessage().to_string().c_str());

    CommunicationFrame fc(20, 1, 1);
    tb->append("\nReversed Data: ");
    tb->append(fc.getEncodedMessage().to_string().c_str());
}

MainWindow::~MainWindow()
{
    delete ui;
}

