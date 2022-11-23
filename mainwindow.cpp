#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("Coded component");
    ui->tabWidget->addTab(new QWidget, "Coded tab");
}

MainWindow::~MainWindow()
{
    delete ui;
}

