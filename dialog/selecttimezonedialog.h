#ifndef SELECTTIMEZONEDIALOG_H
#define SELECTTIMEZONEDIALOG_H

#include <QDialog>
#include <QComboBox>

#include <QDateTime>
#include <QTimeZone>
#include <QList>

#include <QDebug>

namespace Ui {
class SelectTimeZoneDialog;
}

class SelectTimeZoneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectTimeZoneDialog(QWidget *parent = 0);
    ~SelectTimeZoneDialog();
    void setTimeZone(const QByteArray &timeZoneId);
    QByteArray getSelectedTimeZone();

private slots:
    void on_buttonBox_accepted();
    void on_timeZoneComboBox_activated(int index);

private:
    Ui::SelectTimeZoneDialog *ui;
    QComboBox *timeZoneComboBox;
    QByteArray selectedTimeZone;
};

#endif // SELECTTIMEZONEDIALOG_H
