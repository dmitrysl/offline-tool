#include "cronossitexmlparser.h"

CronosSiteXmlParser::CronosSiteXmlParser()
{
    initializeInpuXmlTokenMap();
}

CronosSiteXmlParser::~CronosSiteXmlParser()
{

}

void CronosSiteXmlParser::initializeInpuXmlTokenMap()
{
    inputXmlTokens.insert(InputXmlToken::NO_TOKEN, "");
    inputXmlTokens.insert(InputXmlToken::DICTIONARY, "Dictionary");
    inputXmlTokens.insert(InputXmlToken::ISSUE_STATUSES, "IssueStatuses");
    inputXmlTokens.insert(InputXmlToken::ISSUE_STATUS, "IssueStatus");
    inputXmlTokens.insert(InputXmlToken::ISSUE_TYPES, "IssueTypes");
    inputXmlTokens.insert(InputXmlToken::ISSUE_TYPE, "IssueType");
    inputXmlTokens.insert(InputXmlToken::IS_ROLLBACK, "IsRollback");
    inputXmlTokens.insert(InputXmlToken::PRIORITIES, "Priorities");
    inputXmlTokens.insert(InputXmlToken::PRIORITY, "Priority");
    inputXmlTokens.insert(InputXmlToken::REASON_TYPES, "ReasonTypes");
    inputXmlTokens.insert(InputXmlToken::REASSON_TYPE, "ReasonType");
    inputXmlTokens.insert(InputXmlToken::RESPONSIBLE_PARTIES, "ResponsibleParties");
    inputXmlTokens.insert(InputXmlToken::QUALITY_ITEMS, "QualityItems");
    inputXmlTokens.insert(InputXmlToken::SITES, "Sites");
    inputXmlTokens.insert(InputXmlToken::SITE, "Site");
    inputXmlTokens.insert(InputXmlToken::TOKEN, "Token");
    inputXmlTokens.insert(InputXmlToken::PROJECT, "Project");
    inputXmlTokens.insert(InputXmlToken::WORKPACKAGE, "Workpackage");
    inputXmlTokens.insert(InputXmlToken::SITE_LOG, "SiteLog");
    inputXmlTokens.insert(InputXmlToken::MESSAGE, "Message");
    inputXmlTokens.insert(InputXmlToken::SITE_DETAILS, "SiteDetails");
    inputXmlTokens.insert(InputXmlToken::IS_EDITABLE, "IsEditable");
    inputXmlTokens.insert(InputXmlToken::ID, "Id");
    inputXmlTokens.insert(InputXmlToken::NAME, "Name");
    inputXmlTokens.insert(InputXmlToken::CONTENT, "Content");
    inputXmlTokens.insert(InputXmlToken::CREATED_AT, "CreatedAt");
    inputXmlTokens.insert(InputXmlToken::CREATED_BY, "CreatedBy");
    inputXmlTokens.insert(InputXmlToken::UPDATED_AT, "UpdatedAt");
    inputXmlTokens.insert(InputXmlToken::UPDATED_BY, "UpdatedBy");
    inputXmlTokens.insert(InputXmlToken::SWP_ID, "SwpId");
    inputXmlTokens.insert(InputXmlToken::CSC, "Csc");
    inputXmlTokens.insert(InputXmlToken::SITE_NAME, "SiteName");
    inputXmlTokens.insert(InputXmlToken::STARTED_AT, "StartedAt");
    inputXmlTokens.insert(InputXmlToken::FORECAST, "Forecast");
    inputXmlTokens.insert(InputXmlToken::IPM_WP_ID, "IpmWpId");
    inputXmlTokens.insert(InputXmlToken::IPM_PHASE, "IpmPhase");
    inputXmlTokens.insert(InputXmlToken::PARTNER, "Partner");
    inputXmlTokens.insert(InputXmlToken::CONTACT_NUMBER, "ContactNumber");
    inputXmlTokens.insert(InputXmlToken::PERMISSION_ID, "PermissionId");
    inputXmlTokens.insert(InputXmlToken::CHECKLISTS, "Checklists");
    inputXmlTokens.insert(InputXmlToken::CHECKLIST, "Checklist");
    inputXmlTokens.insert(InputXmlToken::SERVICE, "Service");
    inputXmlTokens.insert(InputXmlToken::SCOPE, "Scope");
    inputXmlTokens.insert(InputXmlToken::TECHNOLOGY, "Technology");
    inputXmlTokens.insert(InputXmlToken::ISSUE_LOG, "IssueLog");
    inputXmlTokens.insert(InputXmlToken::ISSUE, "Issue");
    inputXmlTokens.insert(InputXmlToken::QUALITY_ITEM, "QualityItem");
    inputXmlTokens.insert(InputXmlToken::RESPONSIBLE_PARTY, "ResponsibleParty");
    inputXmlTokens.insert(InputXmlToken::STATUS, "Status");
    inputXmlTokens.insert(InputXmlToken::DESCRIPTION, "Description");
    inputXmlTokens.insert(InputXmlToken::ADDITIONAL_FIELDS, "AdditionalFields");
    inputXmlTokens.insert(InputXmlToken::FIELD, "Field");
    inputXmlTokens.insert(InputXmlToken::VALUE, "Value");
    inputXmlTokens.insert(InputXmlToken::TYPE, "Type");
    inputXmlTokens.insert(InputXmlToken::OPTIONS, "Options");
    inputXmlTokens.insert(InputXmlToken::OPTION, "Option");
    inputXmlTokens.insert(InputXmlToken::PHASES, "Phases");
    inputXmlTokens.insert(InputXmlToken::PHASE, "Phase");
    inputXmlTokens.insert(InputXmlToken::ITEMS, "Items");
    inputXmlTokens.insert(InputXmlToken::ITEM, "Item");
    inputXmlTokens.insert(InputXmlToken::PREDEFINED, "Predefined");
    inputXmlTokens.insert(InputXmlToken::MANDATORY, "Mandatory");
    inputXmlTokens.insert(InputXmlToken::COMPLETED_AT, "CompletedAt");
    inputXmlTokens.insert(InputXmlToken::COMMENT, "Comment");
    inputXmlTokens.insert(InputXmlToken::DEPENDENCIES, "Dependencies");
    inputXmlTokens.insert(InputXmlToken::DEPENDENCY, "Dependency");
    inputXmlTokens.insert(InputXmlToken::PLANNED_START_DATE, "PlannedStartDate");
    inputXmlTokens.insert(InputXmlToken::PLANNING_TOOLS, "PlanningTools");
    inputXmlTokens.insert(InputXmlToken::PLANNING_TOOL, "PlanningTool");
    inputXmlTokens.insert(InputXmlToken::IS_SELECTED, "IsSelected");
}

void CronosSiteXmlParser::updateProgress(qint64 currentPosition)
{
    qDebug() << "-----------";
    qDebug() << fileSize;
    qDebug() << currentPosition;
    int progress = (int) (((double) currentPosition / fileSize) * 100);
    qDebug() << progress;
    emit updateProgress(progress);
}

void CronosSiteXmlParser::parseXmlFile(QFile &file)
{
    emit updateProgress(0);

    fileSize = file.size();

    QXmlStreamReader xml(&file);

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[InputXmlToken::DICTIONARY])
                dictionary = parseDictionary(xml);

            if (xml.name() == inputXmlTokens[InputXmlToken::SITES])
                continue;

            if (xml.name() == inputXmlTokens[InputXmlToken::SITE])
            {
                updateProgress(xml.characterOffset());
                sites.append(parseSite(xml));
            }
        }
    }
    updateProgress(100);
}

Dictionary CronosSiteXmlParser::getDictionary()
{
    return dictionary;
}

QList<QSharedPointer<Site>> CronosSiteXmlParser::getSites()
{
    return sites;
}

void CronosSiteXmlParser::clear()
{
    sites.clear();
}

Dictionary CronosSiteXmlParser::parseDictionary(QXmlStreamReader &xml)
{
    Dictionary dictionary;
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::DICTIONARY])
        return dictionary;

    xml.readNext();

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::DICTIONARY]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_STATUSES])
                dictionary.IssueStatuses = parseIssueStatuses(xml);

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_TYPES])
                dictionary.IssueTypes = parseIssueTypes(xml);

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::PRIORITIES])
                dictionary.Priorities = parsePriorities(xml);

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::REASON_TYPES])
                dictionary.ReasonTypes = parseReasonTypes(xml);

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::RESPONSIBLE_PARTIES])
                dictionary.IssueResponsibleParties = parseIssueResponsibleParties(xml);

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::QUALITY_ITEMS])
                dictionary.IssueQualityItems = parseIssueQualityItems(xml);
        }
        xml.readNext();
    }

    return dictionary;
}

QList<IssueStatus> CronosSiteXmlParser::parseIssueStatuses(QXmlStreamReader &xml)
{
    QList<IssueStatus> issueStatuses;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_STATUSES])
        return issueStatuses;

    xml.readNext();

    IssueStatus issueStatus;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_STATUS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_STATUS])
        {
            issueStatus = {0};
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                issueStatus.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                issueStatus.Name = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_STATUS])
        {
            issueStatuses.append(issueStatus);
        }
        xml.readNext();
    }

    return issueStatuses;
}

QList<IssueType> CronosSiteXmlParser::parseIssueTypes(QXmlStreamReader &xml)
{
    QList<IssueType> issueTypes;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_TYPES])
        return issueTypes;

    xml.readNext();

    IssueType issueType;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_TYPES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_TYPE])
        {
            issueType = {0};
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                issueType.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                issueType.Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::IS_ROLLBACK])
            {
                xml.readNext();
                issueType.IsRollback = xml.text().toString() == "true";
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_TYPE])
        {
            issueTypes.append(issueType);
        }
        xml.readNext();
    }

    return issueTypes;
}

QList<Priority> CronosSiteXmlParser::parsePriorities(QXmlStreamReader &xml)
{
    QList<Priority> priorities;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PRIORITIES])
        return priorities;

    xml.readNext();

    Priority priority;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PRIORITIES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PRIORITY])
        {
            priority = {0};
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                priority.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                priority.Name = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PRIORITY])
        {
            priorities.append(priority);
        }
        xml.readNext();
    }

    return priorities;
}

QList<ReasonType> CronosSiteXmlParser::parseReasonTypes(QXmlStreamReader &xml)
{
    QList<ReasonType> reasonTypes;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::REASON_TYPES])
        return reasonTypes;

    xml.readNext();

    ReasonType reasonType;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::REASON_TYPES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::REASSON_TYPE])
        {
            reasonType = {0};
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                reasonType.Id = xml.text().toString().toInt();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                reasonType.Name = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::REASSON_TYPE])
        {
            reasonTypes.append(reasonType);
        }
        xml.readNext();
    }

    return reasonTypes;
}

QList<IssueResponsibleParty> CronosSiteXmlParser::parseIssueResponsibleParties(QXmlStreamReader &xml)
{
    QList<IssueResponsibleParty> issueResponsibleParties;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::RESPONSIBLE_PARTIES])
        return issueResponsibleParties;

    xml.readNext();

    IssueResponsibleParty responsibleParty;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::RESPONSIBLE_PARTIES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::RESPONSIBLE_PARTY])
        {
            responsibleParty = {0};
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                responsibleParty.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                responsibleParty.Name = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::RESPONSIBLE_PARTY])
        {
            issueResponsibleParties.append(responsibleParty);
        }
        xml.readNext();
    }

    return issueResponsibleParties;
}

QList<IssueQualityItem> CronosSiteXmlParser::parseIssueQualityItems(QXmlStreamReader &xml)
{
    QList<IssueQualityItem> issueQualityItems;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::QUALITY_ITEMS])
        return issueQualityItems;

    xml.readNext();

    IssueQualityItem qualityItem;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::QUALITY_ITEMS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::QUALITY_ITEM])
        {
            qualityItem = {0};
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                qualityItem.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                qualityItem.Name = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::QUALITY_ITEM])
        {
            issueQualityItems.append(qualityItem);
        }
        xml.readNext();
    }

    return issueQualityItems;
}

QSharedPointer<Site> CronosSiteXmlParser::parseSite(QXmlStreamReader &xml)
{
    QSharedPointer<Site> site = QSharedPointer<Site>(new Site);
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::SITE])
        return site;

    QXmlStreamAttributes attributes = xml.attributes();
    if (attributes.hasAttribute(inputXmlTokens[CronosSiteXmlParser::TOKEN]))
        site.data()->Token = attributes.value(inputXmlTokens[CronosSiteXmlParser::TOKEN]).toString();
    else
        return site;

    xml.readNext();

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::SITE]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::PROJECT])
            {
                site.data()->project = parseProject(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::WORKPACKAGE])
            {
                site.data()->workPackage = parseWorkPackage(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::SITE_LOG])
            {
                site.data()->SiteLog = parseSiteLogMessages(xml);
                emit updateProgress((int) (xml.characterOffset() / fileSize) * 100);
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::SITE_DETAILS])
            {
                site.data()->siteDetails = parseSiteDetails(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::CHECKLISTS])
            {
                site.data()->Checklists.append(parseChecklists(xml));
            }
        }
        xml.readNext();
    }
    return site;
}

Project CronosSiteXmlParser::parseProject(QXmlStreamReader &xml)
{
    Project project;
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PROJECT])
        return project;

    xml.readNext();

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PROJECT]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                project.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                project.Name = xml.text().toString();
            }
        }

        xml.readNext();
    }
    return project;
}

WorkPackage CronosSiteXmlParser::parseWorkPackage(QXmlStreamReader &xml)
{
    WorkPackage workPackage;
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::WORKPACKAGE])
        return workPackage;

    xml.readNext();

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::WORKPACKAGE]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                workPackage.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                workPackage.Name = xml.text().toString();
            }
        }

        xml.readNext();
    }
    return workPackage;
}

QList<QSharedPointer<Message>> CronosSiteXmlParser::parseSiteLogMessages(QXmlStreamReader &xml)
{
    QList<QSharedPointer<Message>> messages;

    xml.readNext();

    QSharedPointer<Message> message;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::SITE_LOG]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::MESSAGE])
        {
            message = QSharedPointer<Message>(new Message);
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                message.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::CONTENT])
            {
                xml.readNext();
                message.data()->Content = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::CREATED_AT])
            {
                xml.readNext();
                message.data()->CreatedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                message.data()->CreatedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::CREATED_BY])
            {
                xml.readNext();
                message.data()->CreatedBy = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::UPDATED_AT])
            {
                xml.readNext();
                message.data()->UpdatedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                message.data()->UpdatedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::UPDATED_BY])
            {
                xml.readNext();
                message.data()->UpdatedBy = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::MESSAGE])
        {
            messages.append(message);
        }

        xml.readNext();
    }

    return messages;
}

SiteDetails CronosSiteXmlParser::parseSiteDetails(QXmlStreamReader &xml)
{
    SiteDetails siteDetails;
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::SITE_DETAILS])
        return siteDetails;

    xml.readNext();

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::SITE_DETAILS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::SWP_ID])
            {
                xml.readNext();
                siteDetails.SwpId = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::CSC])
            {
                xml.readNext();
                siteDetails.Csc = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::SITE_NAME])
            {
                xml.readNext();
                siteDetails.SiteName = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::STARTED_AT])
            {
                xml.readNext();
                siteDetails.StartedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                siteDetails.StartedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::FORECAST])
            {
                xml.readNext();
                siteDetails.Forecast = QDate::fromString(xml.text().toString(), DATE_FORMAT);
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::IPM_WP_ID])
            {
                xml.readNext();
                siteDetails.IpmWpId = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::IPM_PHASE])
            {
                xml.readNext();
                siteDetails.IpmPhase = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::PARTNER])
            {
                xml.readNext();
                siteDetails.Partner = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::CONTACT_NUMBER])
            {
                xml.readNext();
                siteDetails.ContactNumber = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::PERMISSION_ID])
            {
                xml.readNext();
                siteDetails.PermissionId = xml.text().toString();
            }
        }

        xml.readNext();
    }
    return siteDetails;
}

QList<QSharedPointer<Checklist>> CronosSiteXmlParser::parseChecklists(QXmlStreamReader &xml)
{
    QList<QSharedPointer<Checklist>> checklists;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::CHECKLISTS])
        return checklists;

    xml.readNext();

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::CHECKLIST])
        return checklists;

    QSharedPointer<Checklist> checklist;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::CHECKLISTS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::CHECKLIST])
        {
            checklist = QSharedPointer<Checklist>(new Checklist);
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                checklist.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                checklist.data()->Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::SERVICE])
            {
                xml.readNext();
                checklist.data()->Service = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::SCOPE])
            {
                xml.readNext();
                checklist.data()->Scope = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::TECHNOLOGY])
            {
                xml.readNext();
                checklist.data()->Technology = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::PLANNED_START_DATE])
            {
                xml.readNext();
                checklist.data()->PlannedStartDate = QDate::fromString(xml.text().toString(), DATE_FORMAT);
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::PLANNING_TOOLS])
            {
                checklist.data()->PlanningTools = parsePlanningTools(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ADDITIONAL_FIELDS])
            {
                checklist.data()->AdditionalFields = parseAdditionalFields(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_LOG])
            {
                checklist.data()->Issues = parseIssues(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::PHASES])
            {
                checklist.data()->ProcessPhases = parseProcessPhases(xml);
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::CHECKLIST])
        {
            checklists.append(checklist);
        }

        xml.readNext();
    }

    return checklists;
}

QList<QSharedPointer<PlanningTool>> CronosSiteXmlParser::parsePlanningTools(QXmlStreamReader &xml)
{
    QList<QSharedPointer<PlanningTool>> planningTools;

    xml.readNext();

    QSharedPointer<PlanningTool> planningTool;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PLANNING_TOOLS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PLANNING_TOOL])
        {
            planningTool = QSharedPointer<PlanningTool>(new PlanningTool);
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                planningTool.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                planningTool.data()->Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::IS_SELECTED])
            {
                xml.readNext();
                planningTool.data()->IsSelected = xml.text().toString() == "true";
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PLANNING_TOOL])
        {
            planningTools.append(planningTool);
        }

        xml.readNext();
    }
    return planningTools;
}

QList<QSharedPointer<AdditionalField>> CronosSiteXmlParser::parseAdditionalFields(QXmlStreamReader &xml)
{
    QList<QSharedPointer<AdditionalField>> additionalFields;

    xml.readNext();

    QSharedPointer<AdditionalField> additionalField;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ADDITIONAL_FIELDS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::FIELD])
        {
            additionalField = QSharedPointer<AdditionalField>(new AdditionalField);
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                additionalField.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                additionalField.data()->Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::TYPE])
            {
                xml.readNext();
                additionalField.data()->Type = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::VALUE])
            {
                xml.readNext();
                additionalField.data()->Value = xml.text().toString();
            }

            // options to be implemented
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::FIELD])
        {
            additionalFields.append(additionalField);
        }

        xml.readNext();
    }
    return additionalFields;
}

QList<QSharedPointer<Issue>> CronosSiteXmlParser::parseIssues(QXmlStreamReader &xml)
{
    QList<QSharedPointer<Issue>> issues;

    xml.readNext();

    QSharedPointer<Issue> issue;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE_LOG]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE])
        {
            issue = QSharedPointer<Issue>(new Issue);
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                issue.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::TYPE])
            {
                xml.readNext();
                issue.data()->Type = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::PHASE])
            {
                xml.readNext();
                issue.data()->Phase = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::QUALITY_ITEM])
            {
                xml.readNext();
                issue.data()->QualityItem = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::RESPONSIBLE_PARTY])
            {
                xml.readNext();
                issue.data()->ResponsibleParty = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::STATUS])
            {
                xml.readNext();
                issue.data()->Status = xml.text().toString().toInt();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::DESCRIPTION])
            {
                xml.readNext();
                issue.data()->Description = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::CREATED_AT])
            {
                xml.readNext();
                issue.data()->CreatedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                issue.data()->CreatedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::CREATED_BY])
            {
                xml.readNext();
                issue.data()->CreatedBy = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::UPDATED_AT])
            {
                xml.readNext();
                issue.data()->UpdatedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                issue.data()->UpdatedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::UPDATED_BY])
            {
                xml.readNext();
                issue.data()->UpdatedBy = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ISSUE])
        {
            issues.append(issue);
        }

        xml.readNext();
    }
    return issues;
}

QList<QSharedPointer<ProcessPhase>> CronosSiteXmlParser::parseProcessPhases(QXmlStreamReader &xml)
{
    QList<QSharedPointer<ProcessPhase>> processPhases;

    xml.readNext();

    QSharedPointer<ProcessPhase> processPhase;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PHASES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PHASE])
        {
            processPhase = QSharedPointer<ProcessPhase>(new ProcessPhase);

            QXmlStreamAttributes attributes = xml.attributes();
            if (attributes.hasAttribute(inputXmlTokens[CronosSiteXmlParser::TYPE]))
                processPhase.data()->Type = attributes.value(inputXmlTokens[CronosSiteXmlParser::TYPE]).toString().toInt();
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                processPhase.data()->Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ITEMS])
            {
                processPhase.data()->Items = parseChecklistItems(xml);
                updateProgress(xml.characterOffset());
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::PHASE])
        {
            processPhases.append(processPhase);
        }

        xml.readNext();
    }
    return processPhases;
}

QList<QSharedPointer<ChecklistItem>> CronosSiteXmlParser::parseChecklistItems(QXmlStreamReader &xml)
{
    QList<QSharedPointer<ChecklistItem>> checklistItems;

    xml.readNext();

    QSharedPointer<ChecklistItem> checklistItem;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ITEMS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ITEM])
        {
            checklistItem = QSharedPointer<ChecklistItem>(new ChecklistItem);

            QXmlStreamAttributes attributes = xml.attributes();
            if (attributes.hasAttribute(inputXmlTokens[CronosSiteXmlParser::MANDATORY]))
                checklistItem.data()->IsMandatory = attributes.value(inputXmlTokens[CronosSiteXmlParser::MANDATORY]).toString() == "true";
            if (attributes.hasAttribute(inputXmlTokens[CronosSiteXmlParser::PREDEFINED]))
                checklistItem.data()->IsPredefined = attributes.value(inputXmlTokens[CronosSiteXmlParser::PREDEFINED]).toString() == "true";
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                checklistItem.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::NAME])
            {
                xml.readNext();
                checklistItem.data()->Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::COMMENT])
            {
                xml.readNext();
                checklistItem.data()->Comment = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::COMPLETED_AT])
            {
                xml.readNext();
                checklistItem.data()->CompletedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                checklistItem.data()->CompletedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::DEPENDENCIES])
            {
                checklistItem.data()->Dependencies = parseChecklistItemDependencies(xml);
                emit updateProgress((int) (xml.characterOffset() / fileSize) * 100);
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::ITEM])
        {
            checklistItems.append(checklistItem);
        }

        xml.readNext();
    }
    return checklistItems;
}

QList<Dependency> CronosSiteXmlParser::parseChecklistItemDependencies(QXmlStreamReader &xml)
{
    QList<Dependency> dependencies;

    xml.readNext();

    Dependency dependency;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::DEPENDENCIES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::DEPENDENCY])
        {
            dependency = {0};
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::ID])
            {
                xml.readNext();
                dependency.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[CronosSiteXmlParser::TYPE])
            {
                xml.readNext();
                dependency.Type = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[CronosSiteXmlParser::DEPENDENCY])
        {
            dependencies.append(dependency);
        }

        xml.readNext();
    }
    return dependencies;
}
