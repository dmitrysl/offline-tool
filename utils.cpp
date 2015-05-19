#include "utils.h"

Utils::Utils()
{

}

Utils::~Utils()
{

}

QSharedPointer<Site> Utils::findSiteBySwpId(QList<QSharedPointer<Site>> sites, const long swpId)
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

QSharedPointer<ChecklistItem> Utils::findChecklistItemById(QSharedPointer<Site> site, const long clItemId, const int processPhaseId)
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

IssueQualityItem Utils::findQualityItemById(const Dictionary &dictionary, const long itemId)
{
    if (dictionary.IssueQualityItems.isEmpty()) return IssueQualityItem();
    foreach (const IssueQualityItem &item, dictionary.IssueQualityItems)
    {
        if (item.Id == itemId) return item;
    }
    return IssueQualityItem();
}

QSharedPointer<PlanningTool> Utils::findPlanningToolById(QList<QSharedPointer<PlanningTool>> planningTools, const long itemId)
{
    QMutableListIterator<QSharedPointer<PlanningTool>> planningToolsIterator(planningTools);
    while(planningToolsIterator.hasNext())
    {
        QSharedPointer<PlanningTool> planningTool = planningToolsIterator.next();
        if (planningTool.data()->Id == itemId) return planningTool;
    }
    return QSharedPointer<PlanningTool>(0);
}

