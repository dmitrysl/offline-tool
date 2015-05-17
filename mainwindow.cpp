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

    selectedTimeZone = QTimeZone(QTimeZone::systemTimeZoneId());

    stateProgress = new QProgressBar(this);
    currentTimeLabel = new QLabel(this);
    selectedTimeZoneLabel = new QLabel(this);

    ui->statusBar->addWidget(currentTimeLabel);
    ui->statusBar->addWidget(stateProgress);
    ui->statusBar->addWidget(selectedTimeZoneLabel);

    currentTimeLabel->setVisible(true);
    stateProgress->setVisible(false);
    selectedTimeZoneLabel->setVisible(true);

    currentTimeLabel->setMinimumWidth(200);
    selectedTimeZoneLabel->setMinimumHeight(30);

    ui->exportButton->setDisabled(true);
    ui->selectSites->setDisabled(true);

    ui->clItemCompletedAtDateTime->setDateTimeRange(QDateTime(QDate(2015, 2, 25), QTime(11, 35)), QDateTime(QDate(2016, 2, 25), QTime(11, 35)));
    ui->clItemCompletedAtDateTime->setDisplayFormat(QString(DATE_TIME_FORMAT));
    ui->clItemCompletedAtDateTime->setCalendarPopup(true);


    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete validator;
    delete parser;
    delete generator;
    sites.detach();
    delete DATE_FORMAT;
    delete DATE_TIME_FORMAT;
    killTimer(timerId);
}

void MainWindow::initialize()
{
    QFile schemaFile(QString(":/cronos_export_xml_schema"));
    schemaFile.open(QIODevice::ReadOnly);
    const QByteArray data = schemaFile.readAll();
    schemaText = QString::fromUtf8(data);

    validator = new ImportXmlValidator(this);
    parser = new CronosSiteXmlParser(this);
    generator = new ExportCronosSiteXmlGenerator(this);

    QObject::connect(validator, SIGNAL(validationStatus(bool,ExportXmlFileValidationMessageHandler*)), this, SLOT(importValidationStatus(bool, ExportXmlFileValidationMessageHandler*)));
    QObject::connect(parser, SIGNAL(updateProgress(int)), stateProgress, SLOT(setValue(int)));
    //QObject::connect(generator, SIGNAL(updateProgress(int)), stateProgress, SLOT(setValue(int)));

    selectedTimeZoneLabel->setText(selectedTimeZone.id());

    timerId = startTimer(1000);

    updateVisabilityOfSiteDetailsSection(true, true);
    updateIssueLogStatus(true, true);
    updateChecklistItemStatus(true);

    quickDateInsert = false;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    currentTimeLabel->setText(QDateTime::currentDateTimeUtc().toTimeZone(selectedTimeZone).toString(DATE_TIME_FORMAT));
}

void MainWindow::importValidationStatus(bool errorOccurred, ExportXmlFileValidationMessageHandler *messageHandler)
{
    qDebug() << errorOccurred;
    qDebug() << messageHandler->statusMessage();
    qDebug() << messageHandler->line();
    qDebug() << messageHandler->column();

    importFailed = errorOccurred;

    if (!errorOccurred)
    {
        return;
    }

    QString message = messageHandler->statusMessage()
            + "<div><strong>Error</strong> occurred at line: " + QString::number(messageHandler->line())
            + ", column: " + QString::number(messageHandler->column()) + " of imported xml file.</div>";
    QMessageBox::warning(this, QString("Offline Tool Notification"), message);
}

void MainWindow::on_browseFileButton_clicked()
{
    importFailed = false;
    sites.clear();
    initializeViewTable();
    loadFilterData();
    updateIssueLogStatus(true, true);

    QString filename = QFileDialog::getOpenFileName(this, tr("Open Xml"), ".", tr("Xml files (*.xml)"));

    qDebug() << filename;

    statusBar()->showMessage(tr("Opening xml file."));

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error: Cannot read file " << qPrintable(filename)
         << ": " << qPrintable(file.errorString());

        statusBar()->showMessage(tr("In order to continue, select xml file."), 2000);
        return;
    }

    statusBar()->showMessage(tr("Reading xml file."));
    const QByteArray data = file.readAll();

    statusBar()->showMessage(tr("Validating xml file."));
    //validator->validate(schemaText.toUtf8(), data);

    if (importFailed)
    {
        statusBar()->showMessage(tr("Error occurred during parsing xml file"), 4000);
        file.close();
        return;
    }

    statusBar()->showMessage(tr("Parsing xml file."));

    stateProgress->setVisible(true);
    parser->clear();
    parser->parseXmlFile(data, file.size());
    dictionary = parser->getDictionary();
    sites = parser->getSites();

    stateProgress->setVisible(false);

    file.close();

    initializeViewTable();

    statusBar()->showMessage(tr("Xml Loaded"), 4000);

    if (sites.isEmpty())
    {
        QMessageBox::warning(this, QString("Offline Tool Notification"), QString("No sites were imported. Please check xml file."));
        return;
    }

    if (dictionary.isIssueLogDataEmpty())
    {
        QMessageBox::warning(this, QString("Offline Tool Notification"), QString("No data for issue log. Work with issues is disabled."));
    }

    loadDictionaryData();
    loadFilterData();

    ui->exportButton->setDisabled(false);
}

void MainWindow::loadFilterData()
{
    ui->projectComboBox->clear();
    ui->wpComboBox->clear();

    QList<Project> projects;
    QList<WorkPackage> workPackages;

    QMutableListIterator<QSharedPointer<Site>> siteIterator(sites);
    while(siteIterator.hasNext())
    {
        QSharedPointer<Site> site = siteIterator.next();
        if (!projects.contains(site.data()->project))
        {
            projects.append(site.data()->project);
        }
        if (!workPackages.contains(site.data()->workPackage))
        {
            workPackages.append(site.data()->workPackage);
        }
    }

    foreach (const Project &project, projects)
    {
        ui->projectComboBox->addItem(project.Name, QVariant(QString::number(project.Id)));
    }
    foreach (const WorkPackage &workPackage, workPackages)
    {
        ui->wpComboBox->addItem(workPackage.Name, QVariant(QString::number(workPackage.Id)));
    }
}

void MainWindow::loadDictionaryData()
{
    updateIssueLogStatus(true, true);
    if (dictionary.isIssueLogDataEmpty()) {
        return;
    }

    ui->issueStatus->clear();
    ui->issuePhase->clear();
    ui->issueStatus->clear();

    foreach (const IssueStatus &issueStatus, dictionary.IssueStatuses)
    {
        ui->issueStatus->addItem(issueStatus.Name, QVariant(QString::number(issueStatus.Id)));
    }

    foreach (const ReasonType &reasonType, dictionary.ReasonTypes)
    {
        ui->issueReasonValue->addItem(reasonType.Name, QVariant(QString::number(reasonType.Id)));
    }

    foreach (const IssueQualityItem &qualityItem, dictionary.IssueQualityItems)
    {
        ui->issueQualityItem->addItem("(" + qualityItem.Code + ") " + qualityItem.Name, QVariant(QString::number(qualityItem.Id)));
    }
    updateIssueLogStatus(false, true);
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
                item = new QStandardItem(checklistItem.data()->CompletedAt.toTimeZone(selectedTimeZone).toString(DATE_FORMAT));
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

    int row = index.row();
    int col = index.column();

    qDebug() << sites.at(row).data()->siteDetails.Csc;
    qDebug() << model->headerData(row, Qt::Vertical).toString();
    qDebug() << model->headerData(col, Qt::Horizontal).toString();

    QVariant swpDetails = index.data(TableCellDataType::SWP_ID);

    if (!swpDetails.isValid()) {
        updateIssueLogStatus(true, true);
        updateSiteDetailsSection(QSharedPointer<Site>(0), QSharedPointer<ChecklistItem>(0));
    }

    const long swpId = index.data(TableCellDataType::SWP_ID).toString().toLong();
    const int processPhaseId = index.data(TableCellDataType::PHASE_ID).toString().toInt();
    const long clItemId = index.data(TableCellDataType::CL_ITEM_ID).toString().toLong();

    selectedSite = findSiteBySwpId(swpId);
    selectedChecklistItem = findChecklistItemById(selectedSite, clItemId, processPhaseId);

    updateSiteDetailsSection(selectedSite, selectedChecklistItem);

    if (quickDateInsert)
    {
        QDateTime currentTime = QDateTime::currentDateTimeUtc();
        if (!selectedChecklistItem.isNull())
        {
            qDebug() << "update cl item complete date";
            selectedChecklistItem.data()->CompletedAt = currentTime;
            model->setData(index, currentTime.toTimeZone(selectedTimeZone).toString(TIME_FORMAT));
        }
        return;
    }
}

void MainWindow::updateVisabilityOfSiteDetailsSection(bool isDisabled, bool clearData)
{
    ui->plannedStartDateValue->setDisabled(isDisabled);
    ui->planningToolsValue->setDisabled(isDisabled);
    ui->clItemComment->setDisabled(isDisabled);
    ui->clItemCompletedAtDateTime->setDisabled(isDisabled);
    ui->clItemUpdateButton->setDisabled(isDisabled);
    if (clearData)
    {
        ui->plannedStartDateValue->clear();
        ui->clItemCompletedAtDateTime->clear();
        ui->cscValue->setText(QString(""));
        ui->clItemValue->setText(QString(""));
        ui->clItemComment->setText(QString(""));
    }
}

void MainWindow::updateIssueLogStatus(bool isDisabled, bool clearData)
{
    ui->issueList->setDisabled(isDisabled);
    ui->issueType->setDisabled(isDisabled);
    ui->issuePhase->setDisabled(isDisabled);
    ui->issueStatus->setDisabled(isDisabled);
    ui->issueQualityItem->setDisabled(isDisabled);
    ui->issueResponsibleParty->setDisabled(isDisabled);
    ui->issueReasonValue->setDisabled(isDisabled);
    ui->issueDescription->setDisabled(isDisabled);
    ui->issueUpdatedAtValue->setDisabled(isDisabled);
    ui->issueUpdatedByValue->setDisabled(true);
    ui->issueUpdateButton->setDisabled(isDisabled);
    ui->issueDeleteButton->setDisabled(isDisabled);
    ui->issueRegularCheckbox->setDisabled(isDisabled);
    ui->issueRollbackCheckbox->setDisabled(isDisabled);
    if (clearData)
    {
        ui->issueList->clear();
        ui->issueUpdatedAtValue->clear();
    }
}

void MainWindow::updateChecklistItemStatus(bool isDisabled)
{
    ui->clItemComment->setDisabled(isDisabled);
    ui->clItemCompletedAtDateTime->setDisabled(isDisabled);
    ui->clItemUpdateButton->setDisabled(isDisabled);
}

void MainWindow::updateSiteDetailsSection(QSharedPointer<Site> site, QSharedPointer<ChecklistItem> checklistItem)
{
    ui->phaseComboBox->clear();
    if (site.isNull() || checklistItem.isNull())
    {
        updateVisabilityOfSiteDetailsSection(true, true);
        return;
    }
    updateVisabilityOfSiteDetailsSection(false, true);

    ui->cscValue->setText(site.data()->siteDetails.Csc);
    ui->clItemValue->setText(checklistItem.data()->Name);
    ui->clItemComment->setText(checklistItem.data()->Comment);

    if (checklistItem.data()->CompletedAt.isValid())
    {
        ui->clItemCompletedAtDateTime->setDateTime(checklistItem.data()->CompletedAt);
    }
    else
    {
        ui->clItemCompletedAtDateTime->setDateTime(QDateTime::currentDateTimeUtc().toTimeZone(selectedTimeZone));
    }

    QListIterator<QSharedPointer<Checklist>> checklistsIterator(site.data()->Checklists);
    const QSharedPointer<Checklist> checklist = checklistsIterator.next();

    bool hasNetworkPlanningPhase = false;
    QListIterator<QSharedPointer<ProcessPhase>> phaseIterator(checklist.data()->ProcessPhases);
    while(phaseIterator.hasNext())
    {
        QSharedPointer<ProcessPhase> phase = phaseIterator.next();
        if (phase.data()->Type == 4) hasNetworkPlanningPhase = true;
        ui->phaseComboBox->addItem(phase.data()->Name, QVariant(QString::number(phase.data()->Type)));
    }

    if (hasNetworkPlanningPhase)
    {
        ui->planningToolsValue->clear();
        if (!checklist.data()->PlanningTools.isEmpty())
        {
            const int size = checklist.data()->PlanningTools.size();
            planningToolsModel = new QStandardItemModel(size, 1, this); // 3 rows, 1 col
            for (int i = 0; i < size; i++)
            {
                const QSharedPointer<PlanningTool> planningTool = checklist.data()->PlanningTools.at(i);
                QStandardItem* item = new QStandardItem(planningTool.data()->Name);

                item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
                item->setData(planningTool.data()->IsSelected ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
                item->setData(QVariant(QString::number(planningTool.data()->Id)));
                //QObject::connect(item, SIGNAL(itemChanged(QStandardItem *item)))

                planningToolsModel->setItem(i, 0, item);
            }
            ui->planningToolsValue->setModel(planningToolsModel);
        }
    }
}

QSharedPointer<Site> MainWindow::findSiteBySwpId(const long swpId)
{
    QMutableListIterator<QSharedPointer<Site>> siteIterator(sites);
    while(siteIterator.hasNext())
    {
        QSharedPointer<Site> site = siteIterator.next();
        if (site.data()->siteDetails.SwpId != swpId) continue;
        return site;
    }
    return QSharedPointer<Site>(0);
}

QSharedPointer<ChecklistItem> MainWindow::findChecklistItemById(QSharedPointer<Site> site, const long clItemId, const int processPhaseId)
{
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
            return item;
        }
    }
    return QSharedPointer<ChecklistItem>(0);
}

void MainWindow::on_quickDate_clicked(bool checked)
{
    quickDateInsert = checked;
    qDebug() << quickDateInsert;
}

void MainWindow::on_projectComboBox_activated(int index)
{
    QVariant data = ui->projectComboBox->itemData(index);
    long projectId = data.toString().toLong();
    qDebug() << projectId;
}

void MainWindow::on_wpComboBox_activated(int index)
{
    QVariant data = ui->wpComboBox->itemData(index);
    long wpId = data.toString().toLong();
    qDebug() << wpId;
}

void MainWindow::on_phaseComboBox_activated(int index)
{
    QVariant data = ui->phaseComboBox->itemData(index);
    long phaseId = data.toString().toLong();
    qDebug() << phaseId;
}

void MainWindow::on_actionSelect_Time_Zone_triggered()
{
    selectTimeZoneDialog = new SelectTimeZoneDialog(this);
    selectTimeZoneDialog->setTimeZone(selectedTimeZone.id());
    //selectTimeZoneDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    if (selectTimeZoneDialog->exec())
    {
        selectedTimeZone = QTimeZone(selectTimeZoneDialog->getSelectedTimeZone());
        selectedTimeZoneLabel->setText(selectedTimeZone.id());
        timerEvent(NULL);
        initializeViewTable();
    }
    qDebug() << selectedTimeZone;
}

void MainWindow::on_actionExit_triggered()
{
    qDebug() << "exit from app from main app menu.";
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    aboutDialog = new AboutDialog(this);
    aboutDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    aboutDialog->show();
}

void MainWindow::on_clItemUpdateButton_clicked()
{
    if (selectedChecklistItem.isNull()) return;
    selectedChecklistItem.data()->Comment = ui->clItemComment->toPlainText();
    qDebug() << ui->clItemCompletedAtDateTime->dateTime().toString(DATE_TIME_FORMAT);
    qDebug() << ui->clItemCompletedAtDateTime->dateTime().toTimeZone(QTimeZone("UTC")).toString(DATE_TIME_FORMAT);
    selectedChecklistItem.data()->CompletedAt = ui->clItemCompletedAtDateTime->dateTime().toUTC();
    initializeViewTable();
}

void MainWindow::on_planningToolsValue_activated(int index)
{
    if (selectedSite.isNull()) return;
    QVariant qVariant = ui->planningToolsValue->currentData();
    if (!qVariant.isValid()) return;
    long itemId = qVariant.toString().toLong();
    QList<QSharedPointer<PlanningTool>> planningTools = selectedSite.data()->Checklists.at(0).data()->PlanningTools;
    int numberOfSelectedItems = 0;
    foreach (const QSharedPointer<PlanningTool> planningTool, planningTools)
    {
        if (planningTool.data()->Id == itemId)
        {
            planningTool.data()->IsSelected = !planningTool.data()->IsSelected;
        }
        if (planningTool.data()->IsSelected) numberOfSelectedItems++;
    }
    if (numberOfSelectedItems == 3)
    {
        ui->planningToolsValue->setItemData(index, Qt::Unchecked, Qt::CheckStateRole);
    }
}
