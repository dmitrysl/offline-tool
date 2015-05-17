#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>

#include <QStandardItemModel>
#include <QModelIndex>
#include <QMap>
#include <QSet>

#include "entities.h"
#include "cronossitexmlparser.h"
#include "exportcronossitexmlgenerator.h"
#include "importxmlvalidator.h"
#include "selecttimezonedialog.h"
#include "aboutdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum TableCellDataType
    {
        SWP_ID = 1001,
        PHASE_ID,
        CL_ITEM_ID
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initialize();
    void initializeViewTable();
    void loadFilterData();
    void loadDictionaryData();
    void updateIssueLogStatus(bool isDisabled, bool clearData);
    void updateChecklistItemStatus(bool isDisabled);
    void updateVisabilityOfSiteDetailsSection(bool isDisabled, bool clearData);
    void updateSiteDetailsSection(QSharedPointer<Site> site, QSharedPointer<ChecklistItem> checklistItem);
    QSharedPointer<Site> findSiteBySwpId(const long swpId);
    QSharedPointer<ChecklistItem> findChecklistItemById(QSharedPointer<Site> site, const long clItemId, const int processPhaseId = 0);
    void timerEvent(QTimerEvent *event);

private slots:
    void importValidationStatus(bool errorOccurred, ExportXmlFileValidationMessageHandler *messageHandler);
    void on_browseFileButton_clicked();
    void on_exportButton_clicked();
    void onTableClicked(const QModelIndex &index);
    void on_quickDate_clicked(bool checked);
    void on_projectComboBox_activated(int index);
    void on_wpComboBox_activated(int index);
    void on_phaseComboBox_activated(int index);
    void on_actionAbout_triggered();
    void on_actionSelect_Time_Zone_triggered();
    void on_actionExit_triggered();

    void on_clItemUpdateButton_clicked();

    void on_planningToolsValue_activated(int index);

private:
    Ui::MainWindow *ui;
    QLabel *currentTimeLabel;
    QLabel *selectedTimeZoneLabel;
    QProgressBar *stateProgress;

    SelectTimeZoneDialog *selectTimeZoneDialog;
    AboutDialog *aboutDialog;

    QStandardItemModel *model;
    QStandardItemModel *planningToolsModel;

    bool importFailed;
    ImportXmlValidator *validator;
    CronosSiteXmlParser *parser;
    ExportCronosSiteXmlGenerator *generator;
    QString schemaText;

    Dictionary dictionary;
    QList<QSharedPointer<Site>> sites;
    QList<QSharedPointer<Site>> sitesToView;
    QList<QSharedPointer<Site>> updatedSites;

    QSharedPointer<Site> selectedSite;
    QSharedPointer<ChecklistItem> selectedChecklistItem;

    int timerId;
    bool quickDateInsert;
    QTimeZone selectedTimeZone;

    static constexpr const char* DATE_FORMAT = "dd/MM/yyyy";
    static constexpr const char* TIME_FORMAT = "hh:mm:ss";
    static constexpr const char* DATE_TIME_FORMAT = "dd/MM/yyyy hh:mm:ss";
};

#endif // MAINWINDOW_H
