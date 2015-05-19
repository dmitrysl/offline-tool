#include "importfilexmlparser.h"

ImportFileXmlParser::ImportFileXmlParser(QObject *parent) : QObject(parent)
{
    initializeInpuXmlTokenMap();
}

ImportFileXmlParser::~ImportFileXmlParser()
{

}

void ImportFileXmlParser::initializeInpuXmlTokenMap()
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
    inputXmlTokens.insert(InputXmlToken::CODE, "Code");
    inputXmlTokens.insert(InputXmlToken::PARENT, "Parent");
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

void ImportFileXmlParser::updateProgress(qint64 currentPosition)
{
    qDebug() << "-----------";
    qDebug() << fileSize;
    qDebug() << currentPosition;
    int progress = (int) (((double) currentPosition / fileSize) * 100);
    qDebug() << progress;
    emit updateProgress(progress);
}

void ImportFileXmlParser::parseXmlFile(const QByteArray &data, const qint64 fileSize)
{
    emit updateProgress(0);

    this->fileSize = fileSize;

    QXmlStreamReader xml(data);

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[InputXmlToken::SITES])
                continue;

            if (xml.name() == inputXmlTokens[InputXmlToken::DICTIONARY])
                dictionary = parseDictionary(xml);

            if (xml.name() == inputXmlTokens[InputXmlToken::SITE])
            {
                updateProgress(xml.characterOffset());
                sites.append(parseSite(xml));
            }
        }
    }
    updateProgress(100);
}

Dictionary ImportFileXmlParser::getDictionary()
{
    return dictionary;
}

QList<QSharedPointer<Site>> ImportFileXmlParser::getSites()
{
    return sites;
}

void ImportFileXmlParser::clear()
{
    sites.clear();
}

Dictionary ImportFileXmlParser::parseDictionary(QXmlStreamReader &xml)
{
    Dictionary dictionary;
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::DICTIONARY])
        return dictionary;

    xml.readNext();

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::DICTIONARY]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_STATUSES])
                dictionary.IssueStatuses = parseIssueStatuses(xml);

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_TYPES])
                dictionary.IssueTypes = parseIssueTypes(xml);

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PRIORITIES])
                dictionary.Priorities = parsePriorities(xml);

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::REASON_TYPES])
                dictionary.ReasonTypes = parseReasonTypes(xml);

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::RESPONSIBLE_PARTIES])
                dictionary.IssueResponsibleParties = parseIssueResponsibleParties(xml);

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::QUALITY_ITEMS])
                dictionary.IssueQualityItems = parseIssueQualityItems(xml);
        }
        xml.readNext();
    }

    return dictionary;
}

QList<IssueStatus> ImportFileXmlParser::parseIssueStatuses(QXmlStreamReader &xml)
{
    QList<IssueStatus> issueStatuses;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_STATUSES])
        return issueStatuses;

    xml.readNext();

    IssueStatus issueStatus;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_STATUSES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_STATUS])
        {
            issueStatus = IssueStatus();
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                issueStatus.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                issueStatus.Name = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_STATUS])
        {
            issueStatuses.append(issueStatus);
        }
        xml.readNext();
    }

    return issueStatuses;
}

QList<IssueType> ImportFileXmlParser::parseIssueTypes(QXmlStreamReader &xml)
{
    QList<IssueType> issueTypes;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_TYPES])
        return issueTypes;

    xml.readNext();

    IssueType issueType;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_TYPES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_TYPE])
        {
            issueType = IssueType();
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                issueType.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                issueType.Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::IS_ROLLBACK])
            {
                xml.readNext();
                issueType.IsRollback = xml.text().toString() == "true";
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_TYPE])
        {
            issueTypes.append(issueType);
        }
        xml.readNext();
    }

    return issueTypes;
}

QList<Priority> ImportFileXmlParser::parsePriorities(QXmlStreamReader &xml)
{
    QList<Priority> priorities;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PRIORITIES])
        return priorities;

    xml.readNext();

    Priority priority;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PRIORITIES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PRIORITY])
        {
            priority = Priority();
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                priority.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                priority.Name = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PRIORITY])
        {
            priorities.append(priority);
        }
        xml.readNext();
    }

    return priorities;
}

QList<ReasonType> ImportFileXmlParser::parseReasonTypes(QXmlStreamReader &xml)
{
    QList<ReasonType> reasonTypes;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::REASON_TYPES])
        return reasonTypes;

    xml.readNext();

    ReasonType reasonType;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::REASON_TYPES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::REASSON_TYPE])
        {
            reasonType = ReasonType();
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                reasonType.Id = xml.text().toString().toInt();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                reasonType.Name = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::REASSON_TYPE])
        {
            reasonTypes.append(reasonType);
        }
        xml.readNext();
    }

    return reasonTypes;
}

QList<IssueResponsibleParty> ImportFileXmlParser::parseIssueResponsibleParties(QXmlStreamReader &xml)
{
    QList<IssueResponsibleParty> issueResponsibleParties;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::RESPONSIBLE_PARTIES])
        return issueResponsibleParties;

    xml.readNext();

    IssueResponsibleParty responsibleParty;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::RESPONSIBLE_PARTIES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::RESPONSIBLE_PARTY])
        {
            responsibleParty = IssueResponsibleParty();
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                responsibleParty.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                responsibleParty.Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PARENT])
            {
                xml.readNext();
                responsibleParty.Parent = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PROJECT])
            {
                xml.readNext();
                responsibleParty.Project = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::IPM_WP_TYPE])
            {
                xml.readNext();
                responsibleParty.IpmWpType = xml.text().toString().toInt();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::RESPONSIBLE_PARTY])
        {
            issueResponsibleParties.append(responsibleParty);
        }
        xml.readNext();
    }

    return issueResponsibleParties;
}

QList<IssueQualityItem> ImportFileXmlParser::parseIssueQualityItems(QXmlStreamReader &xml)
{
    QList<IssueQualityItem> issueQualityItems;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::QUALITY_ITEMS])
        return issueQualityItems;

    xml.readNext();

    IssueQualityItem qualityItem;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::QUALITY_ITEMS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::QUALITY_ITEM])
        {
            qualityItem = IssueQualityItem();
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                qualityItem.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                qualityItem.Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::CODE])
            {
                xml.readNext();
                qualityItem.Code = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PHASE])
            {
                xml.readNext();
                qualityItem.Phase = xml.text().toString().toInt();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PARENT])
            {
                xml.readNext();
                qualityItem.Parent = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PROJECT])
            {
                xml.readNext();
                qualityItem.Project = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::IPM_WP_TYPE])
            {
                xml.readNext();
                qualityItem.IpmWpType = xml.text().toString().toInt();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::QUALITY_ITEM])
        {
            issueQualityItems.append(qualityItem);
        }
        xml.readNext();
    }

    return issueQualityItems;
}

QSharedPointer<Site> ImportFileXmlParser::parseSite(QXmlStreamReader &xml)
{
    QSharedPointer<Site> site = QSharedPointer<Site>(new Site);
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::SITE])
        return site;

    QXmlStreamAttributes attributes = xml.attributes();
    if (attributes.hasAttribute(inputXmlTokens[ImportFileXmlParser::TOKEN]))
        site.data()->Token = attributes.value(inputXmlTokens[ImportFileXmlParser::TOKEN]).toString();
    else
        return site;

    xml.readNext();

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::SITE]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PROJECT])
            {
                site.data()->project = parseProject(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::WORKPACKAGE])
            {
                site.data()->workPackage = parseWorkPackage(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::SITE_LOG])
            {
                site.data()->SiteLog = parseSiteLogMessages(xml);
                emit updateProgress((int) (xml.characterOffset() / fileSize) * 100);
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::SITE_DETAILS])
            {
                site.data()->siteDetails = parseSiteDetails(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::CHECKLISTS])
            {
                site.data()->Checklists.append(parseChecklists(xml));
            }
        }
        xml.readNext();
    }
    return site;
}

Project ImportFileXmlParser::parseProject(QXmlStreamReader &xml)
{
    Project project;
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PROJECT])
        return project;

    xml.readNext();

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PROJECT]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                project.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                project.Name = xml.text().toString();
            }
        }

        xml.readNext();
    }
    return project;
}

WorkPackage ImportFileXmlParser::parseWorkPackage(QXmlStreamReader &xml)
{
    WorkPackage workPackage;
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::WORKPACKAGE])
        return workPackage;

    xml.readNext();

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::WORKPACKAGE]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                workPackage.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                workPackage.Name = xml.text().toString();
            }
        }

        xml.readNext();
    }
    return workPackage;
}

QList<QSharedPointer<Message>> ImportFileXmlParser::parseSiteLogMessages(QXmlStreamReader &xml)
{
    QList<QSharedPointer<Message>> messages;

    xml.readNext();

    QSharedPointer<Message> message;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::SITE_LOG]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::MESSAGE])
        {
            message = QSharedPointer<Message>(new Message);
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                message.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::CONTENT])
            {
                xml.readNext();
                message.data()->Content = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::CREATED_AT])
            {
                xml.readNext();
                message.data()->CreatedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                message.data()->CreatedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::CREATED_BY])
            {
                xml.readNext();
                message.data()->CreatedBy = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::UPDATED_AT])
            {
                xml.readNext();
                message.data()->UpdatedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                message.data()->UpdatedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::UPDATED_BY])
            {
                xml.readNext();
                message.data()->UpdatedBy = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::MESSAGE])
        {
            messages.append(message);
        }

        xml.readNext();
    }

    return messages;
}

SiteDetails ImportFileXmlParser::parseSiteDetails(QXmlStreamReader &xml)
{
    SiteDetails siteDetails;
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::SITE_DETAILS])
        return siteDetails;

    xml.readNext();

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::SITE_DETAILS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::SWP_ID])
            {
                xml.readNext();
                siteDetails.SwpId = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::CSC])
            {
                xml.readNext();
                siteDetails.Csc = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::SITE_NAME])
            {
                xml.readNext();
                siteDetails.SiteName = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::STARTED_AT])
            {
                xml.readNext();
                siteDetails.StartedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                siteDetails.StartedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::FORECAST])
            {
                xml.readNext();
                siteDetails.Forecast = QDate::fromString(xml.text().toString(), DATE_FORMAT);
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::IPM_WP_ID])
            {
                xml.readNext();
                siteDetails.IpmWpId = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::IPM_PHASE])
            {
                xml.readNext();
                siteDetails.IpmPhase = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PARTNER])
            {
                xml.readNext();
                siteDetails.Partner = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::CONTACT_NUMBER])
            {
                xml.readNext();
                siteDetails.ContactNumber = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PERMISSION_ID])
            {
                xml.readNext();
                siteDetails.PermissionId = xml.text().toString();
            }
        }

        xml.readNext();
    }
    return siteDetails;
}

QList<QSharedPointer<Checklist>> ImportFileXmlParser::parseChecklists(QXmlStreamReader &xml)
{
    QList<QSharedPointer<Checklist>> checklists;

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::CHECKLISTS])
        return checklists;

    xml.readNext();

    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::CHECKLIST])
        return checklists;

    QSharedPointer<Checklist> checklist;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::CHECKLISTS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::CHECKLIST])
        {
            checklist = QSharedPointer<Checklist>(new Checklist);
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                checklist.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                checklist.data()->Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::SERVICE])
            {
                xml.readNext();
                checklist.data()->Service = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::SCOPE])
            {
                xml.readNext();
                checklist.data()->Scope = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::TECHNOLOGY])
            {
                xml.readNext();
                checklist.data()->Technology = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PLANNED_START_DATE])
            {
                xml.readNext();
                checklist.data()->PlannedStartDate = QDate::fromString(xml.text().toString(), DATE_FORMAT);
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PLANNING_TOOLS])
            {
                checklist.data()->PlanningTools = parsePlanningTools(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ADDITIONAL_FIELDS])
            {
                checklist.data()->AdditionalFields = parseAdditionalFields(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_LOG])
            {
                checklist.data()->Issues = parseIssues(xml);
                updateProgress(xml.characterOffset());
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PHASES])
            {
                checklist.data()->ProcessPhases = parseProcessPhases(xml);
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::CHECKLIST])
        {
            checklists.append(checklist);
        }

        xml.readNext();
    }

    return checklists;
}

QList<QSharedPointer<PlanningTool>> ImportFileXmlParser::parsePlanningTools(QXmlStreamReader &xml)
{
    QList<QSharedPointer<PlanningTool>> planningTools;

    xml.readNext();

    QSharedPointer<PlanningTool> planningTool;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PLANNING_TOOLS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PLANNING_TOOL])
        {
            planningTool = QSharedPointer<PlanningTool>(new PlanningTool);
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                planningTool.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                planningTool.data()->Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::IS_SELECTED])
            {
                xml.readNext();
                planningTool.data()->IsSelected = xml.text().toString() == "true";
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PLANNING_TOOL])
        {
            planningTools.append(planningTool);
        }

        xml.readNext();
    }
    return planningTools;
}

QList<QSharedPointer<AdditionalField>> ImportFileXmlParser::parseAdditionalFields(QXmlStreamReader &xml)
{
    QList<QSharedPointer<AdditionalField>> additionalFields;

    xml.readNext();

    QSharedPointer<AdditionalField> additionalField;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ADDITIONAL_FIELDS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::FIELD])
        {
            additionalField = QSharedPointer<AdditionalField>(new AdditionalField);
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                additionalField.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                additionalField.data()->Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::TYPE])
            {
                xml.readNext();
                additionalField.data()->Type = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::VALUE])
            {
                xml.readNext();
                additionalField.data()->Value = xml.text().toString();
            }

            // options to be implemented
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::FIELD])
        {
            additionalFields.append(additionalField);
        }

        xml.readNext();
    }
    return additionalFields;
}

QList<QSharedPointer<Issue>> ImportFileXmlParser::parseIssues(QXmlStreamReader &xml)
{
    QList<QSharedPointer<Issue>> issues;

    xml.readNext();

    QSharedPointer<Issue> issue;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE_LOG]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE])
        {
            issue = QSharedPointer<Issue>(new Issue);
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                issue.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::TYPE])
            {
                xml.readNext();
                issue.data()->Type = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::PHASE])
            {
                xml.readNext();
                issue.data()->Phase = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::QUALITY_ITEM])
            {
                xml.readNext();
                issue.data()->QualityItem = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::RESPONSIBLE_PARTY])
            {
                xml.readNext();
                issue.data()->ResponsibleParty = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::STATUS])
            {
                xml.readNext();
                issue.data()->Status = xml.text().toString().toInt();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::DESCRIPTION])
            {
                xml.readNext();
                issue.data()->Description = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::CREATED_AT])
            {
                xml.readNext();
                issue.data()->CreatedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                issue.data()->CreatedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::CREATED_BY])
            {
                xml.readNext();
                issue.data()->CreatedBy = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::UPDATED_AT])
            {
                xml.readNext();
                issue.data()->UpdatedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                issue.data()->UpdatedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::UPDATED_BY])
            {
                xml.readNext();
                issue.data()->UpdatedBy = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ISSUE])
        {
            issues.append(issue);
        }

        xml.readNext();
    }
    return issues;
}

QList<QSharedPointer<ProcessPhase>> ImportFileXmlParser::parseProcessPhases(QXmlStreamReader &xml)
{
    QList<QSharedPointer<ProcessPhase>> processPhases;

    xml.readNext();

    QSharedPointer<ProcessPhase> processPhase;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PHASES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PHASE])
        {
            processPhase = QSharedPointer<ProcessPhase>(new ProcessPhase);

            QXmlStreamAttributes attributes = xml.attributes();
            if (attributes.hasAttribute(inputXmlTokens[ImportFileXmlParser::TYPE]))
                processPhase.data()->Type = attributes.value(inputXmlTokens[ImportFileXmlParser::TYPE]).toString().toInt();
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                processPhase.data()->Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ITEMS])
            {
                processPhase.data()->Items = parseChecklistItems(xml);
                updateProgress(xml.characterOffset());
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::PHASE])
        {
            processPhases.append(processPhase);
        }

        xml.readNext();
    }
    return processPhases;
}

QList<QSharedPointer<ChecklistItem>> ImportFileXmlParser::parseChecklistItems(QXmlStreamReader &xml)
{
    QList<QSharedPointer<ChecklistItem>> checklistItems;

    xml.readNext();

    QSharedPointer<ChecklistItem> checklistItem;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ITEMS]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ITEM])
        {
            checklistItem = QSharedPointer<ChecklistItem>(new ChecklistItem);

            QXmlStreamAttributes attributes = xml.attributes();
            if (attributes.hasAttribute(inputXmlTokens[ImportFileXmlParser::MANDATORY]))
                checklistItem.data()->IsMandatory = attributes.value(inputXmlTokens[ImportFileXmlParser::MANDATORY]).toString() == "true";
            if (attributes.hasAttribute(inputXmlTokens[ImportFileXmlParser::PREDEFINED]))
                checklistItem.data()->IsPredefined = attributes.value(inputXmlTokens[ImportFileXmlParser::PREDEFINED]).toString() == "true";
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                checklistItem.data()->Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::NAME])
            {
                xml.readNext();
                checklistItem.data()->Name = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::COMMENT])
            {
                xml.readNext();
                checklistItem.data()->Comment = xml.text().toString();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::COMPLETED_AT])
            {
                xml.readNext();
                checklistItem.data()->CompletedAt = QDateTime::fromString(xml.text().toString(), DATE_TIME_FORMAT);
                checklistItem.data()->CompletedAt.setTimeSpec(Qt::UTC);
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::DEPENDENCIES])
            {
                checklistItem.data()->Dependencies = parseChecklistItemDependencies(xml);
                emit updateProgress((int) (xml.characterOffset() / fileSize) * 100);
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::ITEM])
        {
            checklistItems.append(checklistItem);
        }

        xml.readNext();
    }
    return checklistItems;
}

QList<Dependency> ImportFileXmlParser::parseChecklistItemDependencies(QXmlStreamReader &xml)
{
    QList<Dependency> dependencies;

    xml.readNext();

    Dependency dependency;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::DEPENDENCIES]))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == inputXmlTokens[ImportFileXmlParser::DEPENDENCY])
        {
            dependency = Dependency();
        }

        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == inputXmlTokens[ImportFileXmlParser::ID])
            {
                xml.readNext();
                dependency.Id = xml.text().toString().toLong();
            }

            if (xml.name() == inputXmlTokens[ImportFileXmlParser::TYPE])
            {
                xml.readNext();
                dependency.Type = xml.text().toString();
            }
        }

        if (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == inputXmlTokens[ImportFileXmlParser::DEPENDENCY])
        {
            dependencies.append(dependency);
        }

        xml.readNext();
    }
    return dependencies;
}
