#include <QFileDialog>
#include <QFile>
#include <QDebug>

#include "QStandardItemModel"
#include "QStandardItem"

#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "delegate.h"
#include "exportxmlfilevalidationmessagehandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stateProgress = new QProgressBar(this);
    parser = new CronosSiteXmlParser();
    generator = new ExportCronosSiteXmlGenerator();

    ui->statusBar->addWidget(stateProgress);
    stateProgress->setVisible(false);

    ui->exportButton->setDisabled(true);

    ui->clItemCompletedAtDateTime->setDateTimeRange(QDateTime(QDate(2015, 2, 25), QTime(11, 35)), QDateTime(QDate(2016, 2, 25), QTime(11, 35)));
    ui->clItemCompletedAtDateTime->setDisplayFormat(QString(DATE_TIME_FORMAT));
    ui->clItemCompletedAtDateTime->setCalendarPopup(true);

    QObject::connect(parser, SIGNAL(updateProgress(int)), stateProgress, SLOT(setValue(int)));
    QObject::connect(generator, SIGNAL(updateProgress(int)), stateProgress, SLOT(setValue(int)));
    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete parser;
    delete generator;
    sites.detach();
    delete DATE_FORMAT;
    delete DATE_TIME_FORMAT;
}

void MainWindow::initialize()
{
    QFile schemaFile(QString(":/cronos_export_xml_schema"));
    schemaFile.open(QIODevice::ReadOnly);
    schemaText(QString::fromUtf8(schemaFile.readAll()));
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

    ImportXmlValidator validator;
    validator.validate(schemaText.toUtf8(), file.readAll());

    stateProgress->setVisible(true);
    parser->clear();
    parser->parseXmlFile(file);
    dictionary = parser->getDictionary();
    sites = parser->getSites();

    stateProgress->setVisible(false);

    file.close();

    statusBar()->showMessage(tr("Xml Loaded"), 4000);

    initializeViewTable();

    if (sites.isEmpty())
    {
        QMessageBox::warning(this, QString("Offline Tool Notification"), QString("No sites were imported. Please check xml file."));
        return;
    }

    if (dictionary.isIssueLogDataEmpty())
    {
        QMessageBox::warning(this, QString("Offline Tool Notification"), QString("No data for issue log. Work with issues is disabled."));
    }

    ui->exportButton->setDisabled(false);
}

void MainWindow::initializeViewTable()
{
    model = new QStandardItemModel(this);
    QStandardItem *item;

    QStringList horizontalHeader;
    QStringList verticalHeader;

    QMap<int, QSet<QString>> uniqueClItemNames;
    foreach(QSharedPointer<Site> site, sites)
    {
        verticalHeader.append(site.data()->siteDetails.Csc);
        if (site.data()->Checklists.isEmpty()) continue;
        foreach(QSharedPointer<ProcessPhase> processPhase, site.data()->Checklists[0].data()->ProcessPhases)
        {
            QSet<QString> items = uniqueClItemNames.value(processPhase.data()->Type);
            foreach (QSharedPointer<ChecklistItem> checklistItem, processPhase.data()->Items)
            {
                items.insert(checklistItem.data()->Name);
            }
            uniqueClItemNames.insert(processPhase.data()->Type, items);
        }
    }

    QList<QString> list;
    foreach (int phase, uniqueClItemNames.keys())
    {
        list.append(uniqueClItemNames.value(phase).toList());
    }

    int row = 0;
    int col = 0;
    foreach (QSharedPointer<Site> site, sites)
    {
        foreach (const QString &itemName, list)
        {
            item = new QStandardItem(QString("N/A"));
            item->setEditable(false);
            item->setTextAlignment(Qt::AlignHCenter);
            item->setBackground(QColor(Qt::white));
            item->setForeground(QColor(Qt::black));
            model->setItem(row, col, item);
            col++;
        }
        if (site.data()->Checklists.isEmpty()) continue;
        foreach(QSharedPointer<ProcessPhase> processPhase, site.data()->Checklists[0].data()->ProcessPhases)
        {
            //QList<QString> items = uniqueClItemNames.value(processPhase.Type).toList();
            foreach (QSharedPointer<ChecklistItem> checklistItem, processPhase.data()->Items)
            {
                int index = list.indexOf(checklistItem.data()->Name);
                item = new QStandardItem(checklistItem.data()->CompletedAt.toString(DATE_FORMAT));
                item->setEditable(false);
                item->setTextAlignment(Qt::AlignHCenter);
                item->setBackground(QColor(Qt::white));
                item->setForeground(QColor(Qt::black));
                item->setData(QVariant(QString::number(site.data()->siteDetails.SwpId)), TableCellDataType::SWP_ID);
                item->setData(QVariant(processPhase.data()->Type), TableCellDataType::PHASE_ID);
                item->setData(QVariant(QString::number(checklistItem.data()->Id)), TableCellDataType::CL_ITEM_ID);

                model->setItem(row, index, item);

                if (!checklistItem.data()->Comment.isEmpty())
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

    //ui->tableView->setItemDelegate(new Delegate);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_exportButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Xml"), ".", tr("Xml files (*.xml)"));

    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    stateProgress->setVisible(true);
    generator->generateXmlFile(file, sites, QString("admin"));
    stateProgress->setVisible(false);

    file.close();

    statusBar()->showMessage(tr("Xml file exported"));
}

void MainWindow::onTableClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    QString cellText = index.data().toString();
    qDebug() << cellText;

//    if (!quickDateInsert)
//    {
        QDateTime currentTime = QDateTime::currentDateTimeUtc();
        int row = index.row();
        int col = index.column();

        qDebug() << sites.at(row).data()->siteDetails.Csc;
        qDebug() << model->headerData(row, Qt::Vertical).toString();
        qDebug() << model->headerData(col, Qt::Horizontal).toString();

        long swpId = index.data(TableCellDataType::SWP_ID).toString().toLong();
        int processPhaseId = index.data(TableCellDataType::PHASE_ID).toString().toInt();
        long clItemId = index.data(TableCellDataType::CL_ITEM_ID).toString().toLong();

        qDebug() << "--------- " << sites[0].data()->siteDetails.SwpId;
        QMutableListIterator<QSharedPointer<Site>> siteIterator(sites);
        while(siteIterator.hasNext())
        {
            QSharedPointer<Site> site = siteIterator.next();
            if (site.data()->siteDetails.SwpId != swpId) continue;

            QMutableListIterator<QSharedPointer<Checklist>> checklistsIterator(site.data()->Checklists);
            QMutableListIterator<QSharedPointer<ProcessPhase>> phaseIterator(checklistsIterator.next().data()->ProcessPhases);
            while(phaseIterator.hasNext())
            {
                QSharedPointer<ProcessPhase> phase = phaseIterator.next();
                if (phase.data()->Type != processPhaseId) continue;
                QMutableListIterator<QSharedPointer<ChecklistItem>> clItemIterator(phase.data()->Items);
                while(clItemIterator.hasNext())
                {
                    QSharedPointer<ChecklistItem> item = clItemIterator.next();
                    if (item.data()->Id != clItemId) continue;
                    item.data()->CompletedAt = currentTime;
                    break;
                }
                break;
            }
            break;
        }

        model->setData(index, currentTime.toString(DATE_TIME_FORMAT));

        qDebug() << currentTime.toString(DATE_TIME_FORMAT);

        return;
//    }
}


