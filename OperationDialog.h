#ifndef OPERATIONDIALOG_H
#define OPERATIONDIALOG_H

#include <QDialog>

namespace Ui {
class OperationDialog;
}

class OperationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OperationDialog(std::string message, QWidget *parent = nullptr);
    ~OperationDialog();

private slots:
    void on_buttonBox_helpRequested();

private:
    Ui::OperationDialog *ui;
    std::string message;
};

#endif // OPERATIONDIALOG_H
