#include "selecttimezonedialog.h"
#include "ui_selecttimezonedialog.h"

SelectTimeZoneDialog::SelectTimeZoneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectTimeZoneDialog)
{
    ui->setupUi(this);

    const QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QList<QByteArray> availableTimeZoneIds = QTimeZone::availableTimeZoneIds();
    QList<QTimeZone> qTimeZones;
    foreach (const QByteArray &timeZoneId, availableTimeZoneIds)
    {
        QTimeZone timeZone = QTimeZone(timeZoneId);

        if (timeZone.offsetData(currentDateTime).daylightTimeOffset == -2147483648) continue;

#ifdef QT_DEBUG
        qDebug() << "--------------";
        qDebug() << timeZone.id();
        qDebug() << timeZone.displayName(QTimeZone::StandardTime, QTimeZone::DefaultName);
        qDebug() << timeZone.displayName(QTimeZone::StandardTime, QTimeZone::LongName);
        qDebug() << timeZone.displayName(QTimeZone::StandardTime, QTimeZone::ShortName);
        qDebug() << timeZone.displayName(QTimeZone::StandardTime, QTimeZone::OffsetName);
        qDebug() << "-";

        qDebug() << timeZone.displayName(QTimeZone::GenericTime, QTimeZone::DefaultName);
        qDebug() << timeZone.displayName(QTimeZone::GenericTime, QTimeZone::LongName);
        qDebug() << timeZone.displayName(QTimeZone::GenericTime, QTimeZone::ShortName);
        qDebug() << timeZone.displayName(QTimeZone::GenericTime, QTimeZone::OffsetName);
        qDebug() << "-";

        qDebug() << timeZone.displayName(QTimeZone::DaylightTime, QTimeZone::DefaultName);
        qDebug() << timeZone.displayName(QTimeZone::DaylightTime, QTimeZone::LongName);
        qDebug() << timeZone.displayName(QTimeZone::DaylightTime, QTimeZone::ShortName);
        qDebug() << timeZone.displayName(QTimeZone::DaylightTime, QTimeZone::OffsetName);

        qDebug() << timeZone.offsetData(currentDateTime).abbreviation;
        qDebug() << timeZone.offsetData(currentDateTime).daylightTimeOffset;
        qDebug() << timeZone.offsetData(currentDateTime).standardTimeOffset;
        qDebug() << timeZone.offsetData(currentDateTime).offsetFromUtc;
#endif

        double offset = (double) timeZone.offsetData(currentDateTime).offsetFromUtc / 3600;

#ifdef QT_DEBUG
        if (offset > 0)
            qDebug() << QString("(GMT +%1) $2").arg(offset);
        else
            qDebug() << QString("(GMT %1)").arg(offset);

        qDebug() << "      ";
#endif

        QString("(%1) $2")
                .arg(timeZone.displayName(QTimeZone::GenericTime, QTimeZone::OffsetName))
                .arg(timeZone.displayName(QTimeZone::StandardTime, QTimeZone::DefaultName));

        if (qTimeZones.contains(timeZone)) continue;

        qTimeZones.append(timeZone);
    }

    qSort(qTimeZones.begin(), qTimeZones.end(), [](QTimeZone& a, QTimeZone& b) { const QDateTime currentDateTime = QDateTime::currentDateTimeUtc(); return a.offsetData(currentDateTime).offsetFromUtc < b.offsetData(currentDateTime).offsetFromUtc; });


    foreach (const QTimeZone timeZone, qTimeZones)
    {
        ui->timeZoneComboBox->addItem(timeZone.displayName(QTimeZone::GenericTime, QTimeZone::LongName), QVariant(timeZone.id()));
    }
}

SelectTimeZoneDialog::~SelectTimeZoneDialog()
{
    delete ui;
}

void SelectTimeZoneDialog::setTimeZone(const QByteArray &timeZoneId)
{
    selectedTimeZone = timeZoneId;
    int index = ui->timeZoneComboBox->findData(QVariant(selectedTimeZone));
    if (index != -1)
    { // -1 for not found
       ui->timeZoneComboBox->setCurrentIndex(index);
    }
}

QByteArray SelectTimeZoneDialog::getSelectedTimeZone()
{
    QVariant data = ui->timeZoneComboBox->currentData();
    if (!data.isValid()) return selectedTimeZone;
    selectedTimeZone = data.toByteArray();
    return selectedTimeZone;
}

void SelectTimeZoneDialog::on_buttonBox_accepted()
{
    this->setResult(QDialog::Accepted);

}

void SelectTimeZoneDialog::on_timeZoneComboBox_activated(int index)
{
    QVariant data = ui->timeZoneComboBox->itemData(index);
    if (!data.isValid()) return;
    selectedTimeZone = data.toByteArray();
}
