#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qtextbrowser.h"
#include "CommunicationFrame.h"
#include "CanBus.h"
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
    ui->listWidget->addItem("Coded component");
    ui->tabWidget->addTab(new QWidget, "Coded tab");
    QTextBrowser* tb = ui->tab->findChild<QTextBrowser*>("textBrowser");
//    std::string s = "000001001010000010001000001001"    // initial part of the message
//                    "111011101010011"                   // the crc (which i had to recompute by hand)
//                    "1011111111111";                    // final frame bits
//    std::reverse(s.begin(), s.end());
//    std::bitset<FRAME_MAXIMUM_LENGTH> bs(s);
////    std::cout << bs << '\n';
//    CommunicationFrame cf(bs);
////    std::cout << cf.getEncodedMessage().to_string() << '\n';


//    CommunicationFrame fc(20, 1, 1);
//    tb->append("\nReversed Data: ");
//    tb->append(fc.getEncodedMessage().to_string().c_str());

//    CommunicationFrame fc1(97, 4, (1ULL << 32) - 1);
//    CommunicationFrame fc2(32, 2, 1025);
//    CommunicationFrame fc3(3, 3, 1026);
//    CommunicationFrame fc4(102, 1, 3);
//    CommunicationFrame fc5(66, 1, 44);
//    CommunicationFrame fc6(11, 5, 90);

//    tb->append("Encoded message:");
//    tb->append(fc1.getEncodedMessage().to_string().c_str());
//    tb->append("Encoded message:");
//    tb->append(fc2.getEncodedMessage().to_string().c_str());
//    tb->append("Encoded message:");
//    tb->append(fc3.getEncodedMessage().to_string().c_str());
//    tb->append("Encoded message:");
//    tb->append(fc4.getEncodedMessage().to_string().c_str());
//    tb->append("Encoded message:");
//    tb->append(fc5.getEncodedMessage().to_string().c_str());
//    tb->append("Encoded message:");
//    tb->append(fc6.getEncodedMessage().to_string().c_str());

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

