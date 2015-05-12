#ifndef EXPORTCRONOSSITEXMLGENERATOR_H
#define EXPORTCRONOSSITEXMLGENERATOR_H

#include <QFile>
#include <QList>
#include <QMap>

#include <QXmlStreamWriter>

#include "entities.h"

class ExportCronosSiteXmlGenerator
{
public:
    enum ExportXmlToken {
        NO_TOKEN = 0,
        SITES,
        USER_NAME,
        SITE,
        TOKEN,
        PROJECT,
        WORKPACKAGE,
        SITE_LOG,
        MESSAGE,
        SITE_DETAILS,
        IS_EDITABLE,
        ID,
        NAME,
        CONTENT,
        CREATED_AT,
        CREATED_BY,
        UPDATED_AT,
        UPDATED_BY,
        SWP_ID,
        CSC,
        SITE_NAME,
        STARTED_AT,
        FORECAST,
        IPM_WP_ID,
        IPM_PHASE,
        PARTNER,
        CONTACT_NUMBER,
        PERMISSION_ID,
        CHECKLISTS,
        CHECKLIST,
        SERVICE,
        SCOPE,
        TECHNOLOGY,
        ISSUE_LOG,
        ISSUE,
        QUALITY_ITEM,
        RESPONSIBLE_PARTY,
        STATUS,
        DESCRIPTION,
        ADDITIONAL_FIELDS,
        FIELD,
        VALUE,
        TYPE,
        OPTIONS,
        OPTION,
        PHASES,
        PHASE,
        ITEMS,
        ITEM,
        PREDEFINED,
        MANDATORY,
        COMPLETED_AT,
        COMMENT,
        DEPENDENCIES,
        DEPENDENCY,
        PLANNED_START_DATE,
        PLANNING_TOOLS,
        PLANNING_TOOL,
        IS_SELECTED
    };

    ExportCronosSiteXmlGenerator();
    ~ExportCronosSiteXmlGenerator();
    void generateXmlFile(QFile &file, const QList<Site> &sites, const QString &userName);

private:
    void initializeExportXmlTokenMap();
    void writeSite(QXmlStreamWriter &xmlWriter, const Site &site, const QString &userName);
    void writeSiteLogMessages(QXmlStreamWriter &xmlWriter, const QList<Message> &siteLogMessages);
    void writeChecklists(QXmlStreamWriter &xmlWriter, const QList<Checklist> &checklists);
    void writeChecklist(QXmlStreamWriter &xmlWriter, const Checklist &checklist);
    void writePlanningTools(QXmlStreamWriter &xmlWriter, const QList<PlanningTool> &planningTools);
    void writeAdditionalFields(QXmlStreamWriter &xmlWriter, const QList<AdditionalField> &additionalFields);
    void writeIssueLog(QXmlStreamWriter &xmlWriter, const QList<Issue> &issues);
    void writeChecklistItems(QXmlStreamWriter &xmlWriter, const QList<ChecklistItem> &checklistItems);

private:
    QMap<ExportCronosSiteXmlGenerator::ExportXmlToken, QString> exportXmlTokens;

    static constexpr const char* DATE_FORMAT = "dd/MM/yyyy";
    static constexpr const char* DATE_TIME_FORMAT = "dd/MM/yyyy hh:mm:ss";
};

#endif // EXPORTCRONOSSITEXMLGENERATOR_H
