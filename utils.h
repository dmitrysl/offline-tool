#ifndef UTILS_H
#define UTILS_H


#include "entities.h"

class Utils
{
public:
    Utils();
    ~Utils();

    static QSharedPointer<Site> findSiteBySwpId(QList<QSharedPointer<Site>> sites, const long swpId);
    static QSharedPointer<ChecklistItem> findChecklistItemById(QSharedPointer<Site> site, const long clItemId, const int processPhaseId = 0);
    static IssueQualityItem findQualityItemById(const Dictionary &dictionary, const long itemId);
    static IssueResponsibleParty findResponsiblePartyItemById(const Dictionary &dictionary, const long itemId);
    static QSharedPointer<PlanningTool> findPlanningToolById(QList<QSharedPointer<PlanningTool>> planningTools, const long itemId);
    static QSharedPointer<Issue> findIssueById(QList<QSharedPointer<Issue>> issues, const long itemId);
};

#endif // UTILS_H
