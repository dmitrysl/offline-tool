#ifndef ENTITIES
#define ENTITIES

#include <QSharedPointer>
#include <QString>
#include <QDate>
#include <QDateTime>
#include <QList>


struct IssueStatus
{
    long Id;
    QString Name;
};

struct IssueType
{
    long Id;
    QString Name;
    bool IsRollback;
};

struct Priority
{
    int Id;
    QString Name;
};

struct ReasonType
{
    int Id;
    QString Name;
};

struct IssueResponsibleParty
{
    long Id;
    QString Name;
};

struct IssueQualityItem
{
    long Id;
    QString Name;
};

struct Dictionary
{
    QList<IssueStatus> IssueStatuses;
    QList<IssueType> IssueTypes;
    QList<Priority> Priorities;
    QList<ReasonType> ReasonTypes;
    QList<IssueResponsibleParty> IssueResponsibleParties;
    QList<IssueQualityItem> IssueQualityItems;
    bool isIssueLogDataEmpty()
    {
        return IssueQualityItems.isEmpty() ||
                IssueResponsibleParties.isEmpty() ||
                IssueStatuses.isEmpty() ||
                IssueTypes.isEmpty() ||
                Priorities.isEmpty() ||
                ReasonTypes.isEmpty();
    }
};

struct Message
{
    long Id;
    QString Content;
    QDateTime CreatedAt;
    QString CreatedBy;
    QDateTime UpdatedAt;
    QString UpdatedBy;
};

struct AdditionalField
{
    long Id;
    QString Name;
    QString Value;
    QString Type;
    QList<QString> Options;
};

struct Dependency
{
    long Id;
    QString Type;
};

struct PlanningTool
{
    long Id;
    QString Name;
    bool IsSelected;
};

struct ChecklistItem
{
    long Id;
    QString Name;
    QDateTime CompletedAt;
    QString Comment;
    bool IsPredefined;
    bool IsMandatory;
    QList<Dependency> Dependencies;
};

struct ProcessPhase
{
    int Type;
    QString Name;
    QList<QSharedPointer<ChecklistItem>> Items;
};

struct Issue
{
    long Id;
    long Type;
    long Phase;
    long QualityItem;
    long ResponsibleParty;
    int Status;
    QString Description;
    QDateTime CreatedAt;
    QString CreatedBy;
    QDateTime UpdatedAt;
    QString UpdatedBy;
};

struct Checklist
{
    long Id;
    QString Name;
    QString Service;
    QString Scope;
    QString Technology;
    QDate PlannedStartDate;
    QList<QSharedPointer<PlanningTool>> PlanningTools;
    QList<QSharedPointer<AdditionalField>> AdditionalFields;
    QList<QSharedPointer<Issue>> Issues;
    QList<QSharedPointer<ProcessPhase>> ProcessPhases;
};

struct Project
{
    long Id;
    QString Name;
};

struct WorkPackage
{
    long Id;
    QString Name;
};

struct SiteDetails
{
    long SwpId;
    QString Csc;
    QString SiteName;
    QDateTime StartedAt;
    QDate Forecast;
    long IpmWpId;
    QString IpmPhase;
    QString Partner;
    QString ContactNumber;
    QString PermissionId;
};

struct Site
{
    QString Token;
    Project project;
    WorkPackage workPackage;
    SiteDetails siteDetails;
    QList<QSharedPointer<Message>> SiteLog;
    QList<QSharedPointer<Checklist>> Checklists;
};


#endif // ENTITIES

