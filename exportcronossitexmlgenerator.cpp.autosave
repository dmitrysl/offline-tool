#include "exportcronossitexmlgenerator.h"

ExportCronosSiteXmlGenerator::ExportCronosSiteXmlGenerator()
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

void ExportCronosSiteXmlGenerator::generateXmlFile(QFile &file, const QList<Site> &sites, const QString &userName)
{
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::SITES]);

    foreach (const Site site, sites)
    {
        writeSite(xmlWriter, site, userName);
    }

    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();
}

void ExportCronosSiteXmlGenerator::writeSite(QXmlStreamWriter &xmlWriter, const Site &site, const QString &userName)
{
    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::SITE]);

    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::USER_NAME], userName);
    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::TOKEN], site.Token);
    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::SWP_ID], QString::number(site.siteDetails.SwpId));
    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::STARTED_AT], site.siteDetails.StartedAt.toString(DATE_TIME_FORMAT));

    writeSiteLogMessages(xmlWriter, site.SiteLog);
    writeChecklists(xmlWriter, site.Checklists);

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeSiteLogMessages(QXmlStreamWriter &xmlWriter, const QList<Message> &siteLogMessages)
{
    if (siteLogMessages.isEmpty()) return;

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::SITE_LOG]);

    foreach (const Message message, siteLogMessages)
    {
        xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::MESSAGE]);

        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(message.Id));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::CONTENT], message.Content);
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::CREATED_AT], message.CreatedAt.toString(DATE_TIME_FORMAT));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::CREATED_BY], message.CreatedBy);

        if (message.UpdatedAt.isValid())
            xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::UPDATED_AT], message.UpdatedAt.toString(DATE_TIME_FORMAT));

        if (!message.UpdatedBy.isEmpty())
            xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::UPDATED_BY], message.UpdatedBy);

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeChecklists(QXmlStreamWriter &xmlWriter, const QList<Checklist> &checklists)
{
    if (checklists.isEmpty()) return;

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::CHECKLISTS]);

    foreach (const Checklist checklist, checklists)
    {
        writeChecklist(xmlWriter, checklist);
    }

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeChecklist(QXmlStreamWriter &xmlWriter, const Checklist &checklist)
{
    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::CHECKLIST]);

    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(checklist.Id));
    xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::PLANNED_START_DATE], checklist.PlannedStartDate.toString(DATE_FORMAT));

    writePlanningTools(xmlWriter, checklist.PlanningTools);
    writeAdditionalFields(xmlWriter, checklist.AdditionalFields);
    writeIssueLog(xmlWriter, checklist.Issues);

    QList<ChecklistItem> checklistItems;
    foreach(const ProcessPhase processPhase, checklist.ProcessPhases)
    {
        checklistItems.append(processPhase.Items);
    }

    writeChecklistItems(xmlWriter, checklistItems);

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writePlanningTools(QXmlStreamWriter &xmlWriter, const QList<PlanningTool> &planningTools)
{
    if (planningTools.isEmpty()) return;

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::PLANNING_TOOLS]);

    foreach (const PlanningTool planningTool, planningTools)
    {
        if (!planningTool.IsSelected) continue;

        xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::PLANNING_TOOL]);

        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(planningTool.Id));

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeAdditionalFields(QXmlStreamWriter &xmlWriter, const QList<AdditionalField> &additionalFields)
{
    if (additionalFields.isEmpty()) return;

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::ADDITIONAL_FIELDS]);

    foreach (const AdditionalField additionalField, additionalFields)
    {
        xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::FIELD]);

        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(additionalField.Id));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::VALUE], additionalField.Value);

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeIssueLog(QXmlStreamWriter &xmlWriter, const QList<Issue> &issues)
{
    if (issues.isEmpty()) return;

    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::ISSUE_LOG]);

    foreach (const Issue issue, issues)
    {
        xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::ISSUE]);

        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(issue.Id));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::TYPE], QString::number(issue.Type));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::PHASE], QString::number(issue.Phase));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::QUALITY_ITEM], QString::number(issue.QualityItem));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::RESPONSIBLE_PARTY], QString::number(issue.ResponsibleParty));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::STATUS], QString::number(issue.Status));
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::DESCRIPTION], issue.Description);
        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::CREATED_AT], issue.CreatedAt.toString(DATE_TIME_FORMAT));

        if (issue.UpdatedAt.isValid())
            xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::UPDATED_AT], issue.UpdatedAt.toString(DATE_TIME_FORMAT));

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}

void ExportCronosSiteXmlGenerator::writeChecklistItems(QXmlStreamWriter &xmlWriter, const QList<ChecklistItem> &checklistItems)
{
    xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::ITEMS]);

    foreach(const ChecklistItem checklistItem, checklistItems)
    {
        xmlWriter.writeStartElement(exportXmlTokens[ExportXmlToken::ITEM]);

        xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::ID], QString::number(checklistItem.Id));

        if (checklistItem.CompletedAt.isValid())
            xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::COMPLETED_AT], checklistItem.CompletedAt.toString(DATE_TIME_FORMAT));
        if (!checklistItem.Comment.isEmpty())
            xmlWriter.writeTextElement(exportXmlTokens[ExportXmlToken::COMMENT], checklistItem.Comment);

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}

