#include "OperationDialog.h"
#include "ui_OperationDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

OperationDialog::OperationDialog(std::string message, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperationDialog)
{
    ui->setupUi(this);
    this->message = message;
    ui->plainTextEdit->setPlainText(QString::fromStdString(message));

    QVBoxLayout* outerLayout = new QVBoxLayout();
    setLayout(outerLayout);
    outerLayout->addWidget(ui->plainTextEdit);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    outerLayout->addLayout(buttonsLayout);
    buttonsLayout->addStretch(80);
    buttonsLayout->addWidget(ui->buttonBox);
    setMaximumSize(300, 200);
}

OperationDialog::~OperationDialog()
{
    delete ui;
}

void OperationDialog::on_buttonBox_helpRequested()
{
    ui->plainTextEdit->setPlainText("No one can hear you scream into the void...");
}

