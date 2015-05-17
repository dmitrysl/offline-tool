#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QString details;

    details = "<table>";
    details += "<tr><td style=\"width:15%\">Version</td><td style=\"width:85%\">Info</td></tr>";
    details += "<tr><td style=\"width:15%\">0.0.1</td><td style=\"width:85%\">Initial implementation</td></tr>";
    details += "<tr><td style=\"width:15%\">0.1.0</td><td style=\"width:85%\">Added parser of xml file</td></tr>";
    details += "<tr><td style=\"width:15%\">0.1.1</td><td style=\"width:85%\">Updated parsing of data</td></tr>";
    details += "<tr><td style=\"width:15%\">0.2.0</td><td style=\"width:85%\">Added export data to xml file</td></tr>";
    details += "</table>";

    ui->releaseNotesBrowser->setText(details);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
