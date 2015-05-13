#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>

#include <QStandardItemModel>
#include <QModelIndex>
#include <QMap>
#include <QSet>

#include "entities.h"
#include "cronossitexmlparser.h"
#include "exportcronossitexmlgenerator.h"


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

private slots:
    void on_browseFileButton_clicked();
    void on_exportButton_clicked();
    void onTableClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QProgressBar *stateProgress;
    QStandardItemModel *model;
    CronosSiteXmlParser *parser;
    ExportCronosSiteXmlGenerator *generator;
    QList<QSharedPointer<Site>> sites;
    QList<Site> updatedSites;
    bool quickDateInsert;

    static constexpr const char* DATE_FORMAT = "dd/MM/yyyy";
    static constexpr const char* DATE_TIME_FORMAT = "dd/MM/yyyy hh:mm:ss";
};

#endif // MAINWINDOW_H
