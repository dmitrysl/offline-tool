#ifndef CRONOSSITEXMLPARSER_H
#define CRONOSSITEXMLPARSER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QMap>

#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include "entities.h"


class CronosSiteXmlParser : public QObject
{
    Q_OBJECT

public:
    enum InputXmlToken {
        NO_TOKEN = 0,
        DICTIONARY,
        ISSUE_STATUSES,
        ISSUE_STATUS,
        ISSUE_TYPES,
        ISSUE_TYPE,
        IS_ROLLBACK,
        PRIORITIES,
        PRIORITY,
        REASON_TYPES,
        REASSON_TYPE,
        RESPONSIBLE_PARTIES,
        QUALITY_ITEMS,
        SITES,
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

    explicit CronosSiteXmlParser();
    virtual ~CronosSiteXmlParser();
    void parseXmlFile(QFile &file);
    QList<QSharedPointer<Site>> getResult();
    void clear();

signals:
    void updateProgress(int);

private:
    void initializeInpuXmlTokenMap();
    void updateProgress(qint64 currentPosition);
    Dictionary parseDictionary(QXmlStreamReader &xml);
    QList<IssueStatus> parseIssueStatuses(QXmlStreamReader &xml);
    QList<IssueType> parseIssueTypes(QXmlStreamReader &xml);
    QList<Priority> parsePriorities(QXmlStreamReader &xml);
    QList<ReasonType> parseReasonTypes(QXmlStreamReader &xml);
    QList<IssueResponsibleParty> parseIssueResponsibleParties(QXmlStreamReader &xml);
    QList<IssueQualityItem> parseIssueQualityItems(QXmlStreamReader &xml);
    QSharedPointer<Site> parseSite(QXmlStreamReader &xml);
    Project parseProject(QXmlStreamReader &xml);
    WorkPackage parseWorkPackage(QXmlStreamReader &xml);
    QList<QSharedPointer<Message>> parseSiteLogMessages(QXmlStreamReader &xml);
    SiteDetails parseSiteDetails(QXmlStreamReader &xml);
    QList<QSharedPointer<Checklist>> parseChecklists(QXmlStreamReader &xml);
    QList<QSharedPointer<PlanningTool>> parsePlanningTools(QXmlStreamReader &xml);
    QList<QSharedPointer<AdditionalField>> parseAdditionalFields(QXmlStreamReader &xml);
    QList<QSharedPointer<Issue>> parseIssues(QXmlStreamReader &xml);
    QList<QSharedPointer<ProcessPhase>> parseProcessPhases(QXmlStreamReader &xml);
    QList<QSharedPointer<ChecklistItem>> parseChecklistItems(QXmlStreamReader &xml);
    QList<Dependency> parseChecklistItemDependencies(QXmlStreamReader &xml);

private:
    qint64 fileSize;
    Dictionary dictionary;
    QList<QSharedPointer<Site>> sites;
    QMap<CronosSiteXmlParser::InputXmlToken, QString> inputXmlTokens;

    static constexpr const char* DATE_FORMAT = "dd/MM/yyyy";
    static constexpr const char* DATE_TIME_FORMAT = "dd/MM/yyyy hh:mm:ss";
};

#endif // CRONOSSITEXMLPARSER_H
