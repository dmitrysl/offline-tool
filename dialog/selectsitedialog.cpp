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

QList<QSharedPointer<Site> > SelectSiteDialog::getSelectedSites()
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
        item->setFlags(item->flags() & (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
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
    ui->importedSitesListView->viewport()->installEventFilter(this);
}

bool SelectSiteDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->importedSitesListView->viewport() && event->type() == QEvent::MouseButtonRelease)
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
    return;
    qDebug() << "clicked";
    qDebug() << index.data(DataType::SWP_ID);
    qDebug() << index.data(Qt::CheckStateRole);
    qDebug() << index.row();
    qDebug() << "--";
}

void SelectSiteDialog::on_buttonBox_accepted()
{
    //ui->importedSitesListView->in
}
