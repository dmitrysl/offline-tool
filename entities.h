#ifndef ENTITIES
#define ENTITIES

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
    QList<ChecklistItem> Items;
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
    QList<PlanningTool> PlanningTools;
    QList<AdditionalField> AdditionalFields;
    QList<Issue> Issues;
    QList<ProcessPhase> ProcessPhases;
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
    QList<Message> SiteLog;
    QList<Checklist> Checklists;
};


#endif // ENTITIES
