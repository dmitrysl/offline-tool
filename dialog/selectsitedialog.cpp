#include "selectsitedialog.h"
#include "ui_selectsitedialog.h"

SelectSiteDialog::SelectSiteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectSiteDialog)
{
    ui->setupUi(this);
    connect(ui->importedSitesListView, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked(QModelIndex)));
}

SelectSiteDialog::~SelectSiteDialog()
{
    delete ui;
}

void SelectSiteDialog::setImportedSites(QList<QSharedPointer<Site> > &sites)
{
    importedSites = sites;
    initializeTable();
}

QList<QSharedPointer<Site>> SelectSiteDialog::getSelectedSites()
{
    return selectedSites;
}

void SelectSiteDialog::initializeTable()
{
    model = new QStandardItemModel(importedSites.size(), 1, this);
    QStandardItem *item;

    QStringList verticalHeader;

    int row = 0;
    foreach(QSharedPointer<Site> site, importedSites)
    {
        verticalHeader.append(QString::number(row + 1));

        item = new QStandardItem(site.data()->siteDetails.Csc);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(QVariant(QString::number(site.data()->siteDetails.SwpId)), DataType::SWP_ID);
        item->setCheckable(true);
        item->setTextAlignment(Qt::AlignJustify);
        item->setCheckState(Qt::Unchecked);
        item->setBackground(QColor(Qt::white));
        item->setForeground(QColor(Qt::black));
        model->setItem(row, 0, item);

        row++;
    }

    ui->importedSitesListView->setModel(model);
    ui->importedSitesListView->setSpacing(2);
    ui->importedSitesListView->setDisabled(false);
    ui->importedSitesListView->installEventFilter(this);
}

bool SelectSiteDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease)
    {
        qDebug() << "checked";
        qDebug() << ui->importedSitesListView->currentIndex();
        qDebug() << ui->importedSitesListView->currentIndex().data(DataType::SWP_ID);
        qDebug() << ui->importedSitesListView->currentIndex().data(Qt::CheckStateRole);
        qDebug() << "===";
        //return true;
    }
    return QObject::eventFilter(obj, event);
}

void SelectSiteDialog::clicked(const QModelIndex &index)
{
    if (!index.data(DataType::SWP_ID).isValid()) return;

    long swpId = index.data(DataType::SWP_ID).toString().toLong();

    qDebug() << "clicked";
    qDebug() << swpId;
    qDebug() << index.data(Qt::CheckStateRole);
    qDebug() << index.row();
    qDebug() << "--";

    if (index.data(Qt::CheckStateRole) == Qt::Checked)
    {
        addSite(swpId);
    }
    else
    {
        removeSite(swpId);
    }

}

bool SelectSiteDialog::doesSiteAlreadyAdded(long swpId)
{
    foreach (const QSharedPointer<Site> &site, selectedSites)
    {
        if (site.data()->siteDetails.SwpId == swpId) return true;
    }
    return false;
}

void SelectSiteDialog::addSite(long swpId)
{
    if (doesSiteAlreadyAdded(swpId)) return;
    foreach (const QSharedPointer<Site> &site, importedSites)
    {
        if (site.data()->siteDetails.SwpId != swpId) continue;
        selectedSites.append(site);
        return;
    }
}

void SelectSiteDialog::removeSite(long swpId)
{
    QMutableListIterator<QSharedPointer<Site>> siteIterator(selectedSites);
    while (siteIterator.hasNext()) {
        QSharedPointer<Site> site = siteIterator.next();
        if (site.data()->siteDetails.SwpId != swpId) continue;
        siteIterator.remove();
        return;
    }
}

void SelectSiteDialog::on_buttonBox_accepted()
{
    //ui->importedSitesListView->in
}
