#include "exportcronossitexmlgenerator.h"

ExportCronosSiteXmlGenerator::ExportCronosSiteXmlGenerator(QObject *parent) : QObject(parent)
{
    initializeExportXmlTokenMap();
}

ExportCronosSiteXmlGenerator::~ExportCronosSiteXmlGenerator()
{
    delete DATE_FORMAT;
    delete DATE_TIME_FORMAT;
}

void ExportCronosSiteXmlGenerator::initializeExportXmlTokenMap()
{
    exportXmlTokens.insert(ExportXmlToken::NO_TOKEN, "");
    exportXmlTokens.insert(ExportXmlToken::SITES, "Sites");
    exportXmlTokens.insert(ExportXmlToken::SITE, "Site");
    exportXmlTokens.insert(ExportXmlToken::USER_NAME, "UserName");
    exportXmlTokens.insert(ExportXmlToken::TOKEN, "Token");
    exportXmlTokens.insert(ExportXmlToken::PROJECT, "Project");
    exportXmlTokens.insert(ExportXmlToken::WORKPACKAGE, "Workpackage");
    exportXmlTokens.insert(ExportXmlToken::SITE_LOG, "SiteLog");
    exportXmlTokens.insert(ExportXmlToken::MESSAGE, "Message");
    exportXmlTokens.insert(ExportXmlToken::SITE_DETAILS, "SiteDetails");
    exportXmlTokens.insert(ExportXmlToken::IS_EDITABLE, "IsEditable");
    exportXmlTokens.insert(ExportXmlToken::ID, "Id");
    exportXmlTokens.insert(ExportXmlToken::NAME, "Name");
    exportXmlTokens.insert(ExportXmlToken::CONTENT, "Content");
    exportXmlTokens.insert(ExportXmlToken::CREATED_AT, "CreatedAt");
    exportXmlTokens.insert(ExportXmlToken::CREATED_BY, "CreatedBy");
    exportXmlTokens.insert(ExportXmlToken::UPDATED_AT, "UpdatedAt");
    exportXmlTokens.insert(ExportXmlToken::UPDATED_BY, "UpdatedBy");
    exportXmlTokens.insert(ExportXmlToken::SWP_ID, "SwpId");
    exportXmlTokens.insert(ExportXmlToken::CSC, "Csc");
    exportXmlTokens.insert(ExportXmlToken::SITE_NAME, "SiteName");
    exportXmlTokens.insert(ExportXmlToken::STARTED_AT, "StartedAt");
    exportXmlTokens.insert(ExportXmlToken::FORECAST, "Forecast");
    exportXmlTokens.insert(ExportXmlToken::IPM_WP_ID, "IpmWpId");
    exportXmlTokens.insert(ExportXmlToken::IPM_PHASE, "IpmPhase");
    exportXmlTokens.insert(ExportXmlToken::PARTNER, "Partner");
    exportXmlTokens.insert(ExportXmlToken::CONTACT_NUMBER, "ContactNumber");
    exportXmlTokens.insert(ExportXmlToken::PERMISSION_ID, "PermissionId");
    exportXmlTokens.insert(ExportXmlToken::CHECKLISTS, "Checklists");
    exportXmlTokens.insert(ExportXmlToken::CHECKLIST, "Checklist");
    exportXmlTokens.insert(ExportXmlToken::SERVICE, "Service");
    exportXmlTokens.insert(ExportXmlToken::SCOPE, "Scope");
    exportXmlTokens.insert(ExportXmlToken::TECHNOLOGY, "Technology");
    exportXmlTokens.insert(ExportXmlToken::ISSUE_LOG, "IssueLog");
    exportXmlTokens.insert(ExportXmlToken::ISSUE, "Issue");
    exportXmlTokens.insert(ExportXmlToken::QUALITY_ITEM, "QualityItem");
    exportXmlTokens.insert(ExportXmlToken::RESPONSIBLE_PARTY, "ResponsibleParty");
    exportXmlTokens.insert(ExportXmlToken::STATUS, "Status");
    exportXmlTokens.insert(ExportXmlToken::DESCRIPTION, "Description");
    exportXmlTokens.insert(ExportXmlToken::ADDITIONAL_FIELDS, "AdditionalFields");
    exportXmlTokens.insert(ExportXmlToken::FIELD, "Field");
    exportXmlTokens.insert(ExportXmlToken::VALUE, "Value");
    exportXmlTokens.insert(ExportXmlToken::TYPE, "Type");
    exportXmlTokens.insert(ExportXmlToken::OPTIONS, "Options");
    exportXmlTokens.insert(ExportXmlToken::OPTION, "Option");
    exportXmlTokens.insert(ExportXmlToken::PHASES, "Phases");
    exportXmlTokens.insert(ExportXmlToken::PHASE, "Phase");
    exportXmlTokens.insert(ExportXmlToken::ITEMS, "Items");
    exportXmlTokens.insert(ExportXmlToken::ITEM, "Item");
    exportXmlTokens.insert(ExportXmlToken::PREDEFINED, "Predefined");
    exportXmlTokens.insert(ExportXmlToken::MANDATORY, "Mandatory");
    exportXmlTokens.insert(ExportXmlToken::COMPLETED_AT, "CompletedAt");
    exportXmlTokens.insert(ExportXmlToken::COMMENT, "Comment");
    exportXmlTokens.insert(ExportXmlToken::DEPENDENCIES, "Dependencies");
    exportXmlTokens.insert(ExportXmlToken::DEPENDENCY, "Dependency");
    exportXmlTokens.insert(ExportXmlToken::PLANNED_START_DATE, "PlannedStartDate");
    exportXmlTokens.insert(ExportXmlToken::PLANNING_TOOLS, "PlanningTools");
    exportXmlTokens.insert(ExportXmlToken::PLANNING_TOOL, "PlanningTool");
    exportXmlTokens.insert(ExportXmlToken::IS_SELECTED, "IsSelected");
}

void ExportCronosSiteXmlGenerator::updateProgress(qint64 currentPosition)
{
    qint64 fileSize = 0;
    qDebug() << "-----------";
    qDebug() << fileSize;
    qDebug() << currentPosition;
    int progress = (int) (((double) currentPosition / fileSize) * 100);
    qDebug() << progress;
    emit updateProgress(progress);
}

void ExportCronosSiteXmlGenerator::generateXmlFile(QFile &file, const QList<QSharedPointer<Site>> &sites, const QString &userName)
{
    updateProgress(0);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::SITES]);

    foreach (QSharedPointer<Site> site, sites)
    {
        writeSite(xmlWriter, site, userName);
    }

    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();
    updateProgress(100);
}

void ExportCronosSiteXmlGenerator::writeSite(QXmlStreamWriter &xmlWriter, const QSharedPointer<Site> site, const QString &userName)
{
    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::SITE]);

    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::USER_NAME], userName);
    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::TOKEN], site.data()->Token);
    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::SWP_ID], QString::number(site.data()->siteDetails.SwpId));
    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::STARTED_AT], site.data()->siteDetails.StartedAt.toString(DATE_TIME_FORMAT));

    writeSiteLogMessages(xmlWriter, site.data()->SiteLog);
    writeChecklists(xmlWriter, site.data()->Checklists);

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeSiteLogMessages(QXmlStreamWriter &xmlWriter, const QList<QSharedPointer<Message>> siteLogMessages)
{
    if (siteLogMessages.isEmpty()) return;

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::SITE_LOG]);

    foreach (QSharedPointer<Message> message, siteLogMessages)
    {
        xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::MESSAGE]);

        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(message.data()->Id));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::CONTENT], message.data()->Content);
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::CREATED_AT], message.data()->CreatedAt.toString(DATE_TIME_FORMAT));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::CREATED_BY], message.data()->CreatedBy);

        if (message.data()->UpdatedAt.isValid())
            xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::UPDATED_AT], message.data()->UpdatedAt.toString(DATE_TIME_FORMAT));

        if (!message.data()->UpdatedBy.isEmpty())
            xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::UPDATED_BY], message.data()->UpdatedBy);

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeChecklists(QXmlStreamWriter &xmlWriter, const QList<QSharedPointer<Checklist>> checklists)
{
    if (checklists.isEmpty()) return;

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::CHECKLISTS]);

    foreach (QSharedPointer<Checklist> checklist, checklists)
    {
        writeChecklist(xmlWriter, checklist);
    }

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeChecklist(QXmlStreamWriter &xmlWriter, const QSharedPointer<Checklist> checklist)
{
    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::CHECKLIST]);

    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(checklist.data()->Id));
    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::PLANNED_START_DATE], checklist.data()->PlannedStartDate.toString(DATE_FORMAT));

    writePlanningTools(xmlWriter, checklist.data()->PlanningTools);
    writeAdditionalFields(xmlWriter, checklist.data()->AdditionalFields);
    writeIssueLog(xmlWriter, checklist.data()->Issues);

    QList<QSharedPointer<ChecklistItem>> checklistItems;
    foreach(QSharedPointer<ProcessPhase> processPhase, checklist.data()->ProcessPhases)
    {
        checklistItems.append(processPhase.data()->Items);
    }

    writeChecklistItems(xmlWriter, checklistItems);

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writePlanningTools(QXmlStreamWriter &xmlWriter, const QList<QSharedPointer<PlanningTool>> planningTools)
{
    if (planningTools.isEmpty()) return;

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::PLANNING_TOOLS]);

    foreach (QSharedPointer<PlanningTool> planningTool, planningTools)
    {
        if (!planningTool.data()->IsSelected) continue;

        xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::PLANNING_TOOL]);

        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(planningTool.data()->Id));

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeAdditionalFields(QXmlStreamWriter &xmlWriter, const QList<QSharedPointer<AdditionalField>> additionalFields)
{
    if (additionalFields.isEmpty()) return;

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::ADDITIONAL_FIELDS]);

    foreach (QSharedPointer<AdditionalField> additionalField, additionalFields)
    {
        xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::FIELD]);

        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(additionalField.data()->Id));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::VALUE], additionalField.data()->Value);

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeIssueLog(QXmlStreamWriter &xmlWriter, const QList<QSharedPointer<Issue>> issues)
{
    if (issues.isEmpty()) return;

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::ISSUE_LOG]);

    foreach (QSharedPointer<Issue> issue, issues)
    {
        xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::ISSUE]);

        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(issue.data()->Id));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::TYPE], QString::number(issue.data()->Type));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::PHASE], QString::number(issue.data()->Phase));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::QUALITY_ITEM], QString::number(issue.data()->QualityItem));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::RESPONSIBLE_PARTY], QString::number(issue.data()->ResponsibleParty));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::STATUS], QString::number(issue.data()->Status));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::DESCRIPTION], issue.data()->Description);
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::CREATED_AT], issue.data()->CreatedAt.toString(DATE_TIME_FORMAT));

        if (issue.data()->UpdatedAt.isValid())
            xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::UPDATED_AT], issue.data()->UpdatedAt.toString(DATE_TIME_FORMAT));

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeChecklistItems(QXmlStreamWriter &xmlWriter, const QList<QSharedPointer<ChecklistItem>> checklistItems)
{
    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::ITEMS]);

    foreach(QSharedPointer<ChecklistItem> checklistItem, checklistItems)
    {
        xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::ITEM]);

        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(checklistItem.data()->Id));

        if (checklistItem.data()->CompletedAt.isValid())
            xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::COMPLETED_AT], checklistItem.data()->CompletedAt.toString(DATE_TIME_FORMAT));
        if (!checklistItem.data()->Comment.isEmpty())
            xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::COMMENT], checklistItem.data()->Comment);

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}

