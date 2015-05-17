#include "exportxmlfilevalidationmessagehandler.h"

ExportXmlFileValidationMessageHandler::ExportXmlFileValidationMessageHandler()
{

}

ExportXmlFileValidationMessageHandler::~ExportXmlFileValidationMessageHandler()
{

}

QString ExportXmlFileValidationMessageHandler::statusMessage() const
{
    return m_description;
}

int ExportXmlFileValidationMessageHandler::line() const
{
    return m_sourceLocation.line();
}

int ExportXmlFileValidationMessageHandler::column() const
{
    return m_sourceLocation.column();
}

void ExportXmlFileValidationMessageHandler::handleMessage(QtMsgType type,
                                                          const QString &description,
                                                          const QUrl &identifier,
                                                          const QSourceLocation &sourceLocation)
{
    Q_UNUSED(type);
    Q_UNUSED(identifier);

    m_messageType = type;
    m_description = description;
    m_sourceLocation = sourceLocation;
}
