#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->userNameErrorMessage->setStyleSheet("QLabel { color : red; }");
    ui->userNameErrorMessage->hide();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getUserName()
{
    return ui->userNameEditLine->text().trimmed();
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
    if (ui->userNameEditLine->text().trimmed().isEmpty())
    {
        event->ignore();
        return;
    }
    event->accept();
}

void LoginDialog::on_okButton_clicked()
{
    if (ui->userNameEditLine->text().trimmed().isEmpty())
    {
        ui->userNameErrorMessage->show();
        return;
    }
    QDialog::accept();
}

void LoginDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
