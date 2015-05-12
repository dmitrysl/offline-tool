#include <QFileDialog>
#include <QFile>
#include <QDebug>

#include "QStandardItemModel"
#include "QStandardItem"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->exportButton->setDisabled(true);

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{

}

void MainWindow::on_browseFileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Xml"), ".", tr("Xml files (*.xml)"));

    qDebug() << filename;

    statusBar()->showMessage(tr("Parsing xml file."));

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error: Cannot read file " << qPrintable(filename)
         << ": " << qPrintable(file.errorString());

        statusBar()->showMessage(tr("In order to continue, select xml file."), 2000);
        return;
    }

    CronosSiteXmlParser parser;
    parser.parseXmlFile(file);
    sites = parser.getResult();

    file.close();

    statusBar()->showMessage(tr("Xml Loaded"), 4000);

    initializeViewTable();

    ui->exportButton->setDisabled(false);
}

void MainWindow::initializeViewTable()
{
    model = new QStandardItemModel(2, 4, this);
    QStandardItem *item;

    QStringList horizontalHeader;
    QStringList verticalHeader;

    QMap<int, QSet<QString>> uniqueClItemNames;
    foreach(const Site &site, sites)
    {
        verticalHeader.append(site.siteDetails.Csc);
        if (site.Checklists.isEmpty()) continue;
        foreach(const ProcessPhase &processPhase, site.Checklists[0].ProcessPhases)
        {
            QSet<QString> items = uniqueClItemNames.value(processPhase.Type);
            foreach (ChecklistItem checklistItem, processPhase.Items)
            {
                items.insert(checklistItem.Name);
            }
            uniqueClItemNames.insert(processPhase.Type, items);
        }
    }

    QList<QString> list;
    foreach (int phase, uniqueClItemNames.keys())
    {
        list.append(uniqueClItemNames.value(phase).toList());
    }

    int row = 0;
    int col = 0;
    foreach (const Site &site, sites)
    {
        foreach (const QString &itemName, list)
        {
            item = new QStandardItem(QString("N/A"));
            item->setEditable(false);
            item->setTextAlignment(Qt::AlignHCenter);
            model->setItem(row, col, item);
            col++;
        }
        if (site.Checklists.isEmpty()) continue;
        foreach(const ProcessPhase &processPhase, site.Checklists[0].ProcessPhases)
        {
            //QList<QString> items = uniqueClItemNames.value(processPhase.Type).toList();
            foreach (const ChecklistItem &checklistItem, processPhase.Items)
            {
                int index = list.indexOf(checklistItem.Name);
                item = new QStandardItem(checklistItem.CompletedAt.toString(DATE_FORMAT));
                item->setEditable(false);
                item->setTextAlignment(Qt::AlignHCenter);
                item->setData(QVariant(QString::number(site.siteDetails.SwpId)), TableCellDataType::SWP_ID);
                item->setData(QVariant(processPhase.Type), TableCellDataType::PHASE_ID);
                item->setData(QVariant(QString::number(checklistItem.Id)), TableCellDataType::CL_ITEM_ID);

                model->setItem(row, index, item);

                if (!checklistItem.Comment.isEmpty())
                {
                    item = model->item(row, index);
                    item->setBackground(Qt::yellow);

                }
            }
        }
        row++;
        col = 0;
    }

    horizontalHeader.append(list);

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    model->setColumnCount(horizontalHeader.size());

    ui->tableView->setModel(model);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_exportButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Xml"), ".", tr("Xml files (*.xml)"));

    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    ExportCronosSiteXmlGenerator generator;
    generator.generateXmlFile(file, sites, QString("admin"));

    file.close();

    statusBar()->showMessage(tr("Xml file exported"));
}

void MainWindow::onTableClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    QString cellText = index.data().toString();
    qDebug() << cellText;

    if (!quickDateInsert)
    {
        QDateTime currentTime = QDateTime::currentDateTimeUtc();
        int row = index.row();
        int col = index.column();

        qDebug() << sites.at(row).siteDetails.Csc;
        qDebug() << model->headerData(row, Qt::Vertical).toString();
        qDebug() << model->headerData(col, Qt::Horizontal).toString();

        long swpId = index.data(TableCellDataType::SWP_ID).toString().toLong();
        int processPhaseId = index.data(TableCellDataType::PHASE_ID).toString().toInt();
        long clItemId = index.data(TableCellDataType::CL_ITEM_ID).toString().toLong();


        qDebug() << "--------- " << sites[0].siteDetails.SwpId;
        QMutableListIterator<Site> siteIterator(sites);
        while(siteIterator.hasNext())
        {
            Site site = siteIterator.next();
            if (site.siteDetails.SwpId != swpId) continue;
            QMutableListIterator<ProcessPhase> phaseIterator(site.Checklists[0].ProcessPhases);
            while(phaseIterator.hasNext())
            {
                ProcessPhase phase = phaseIterator.next();
                if (phase.Type != processPhaseId) continue;
                QMutableListIterator<ChecklistItem> clItemIterator(phase.Items);
                while(clItemIterator.hasNext())
                {
                    ChecklistItem item = clItemIterator.next();
                    if (item.Id != clItemId) continue;
                    item.CompletedAt = currentTime;
                    break;
                }
                break;
            }
            break;
        }

        model->setData(index, currentTime.toString(DATE_TIME_FORMAT));
        return;
    }
}

