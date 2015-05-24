#ifndef SELECTSITEDIALOG_H
#define SELECTSITEDIALOG_H

#include <QDebug>
#include <QDialog>
#include <Qlist>

#include <QStandardItemModel>
#include <QStandardItem>
#include <QEvent>

#include "entities.h"

namespace Ui {
class SelectSiteDialog;
}

class SelectSiteDialog : public QDialog
{
    Q_OBJECT

public:
    enum DataType
    {
        SWP_ID = 1001
    };

    explicit SelectSiteDialog(QWidget *parent = 0);
    ~SelectSiteDialog();

    void setImportedSites(QList<QSharedPointer<Site>> &sites);
    QList<QSharedPointer<Site>> getSelectedSites();

private slots:
    void clicked(const QModelIndex &index);

    void on_buttonBox_accepted();

private:
    void initializeTable();
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::SelectSiteDialog *ui;
    QStandardItemModel *model;

    QList<QSharedPointer<Site>> importedSites;
    QList<QSharedPointer<Site>> selectedSites;
};

#endif // SELECTSITEDIALOG_H
