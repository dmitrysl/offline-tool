#include "importxmlfilevalidationmessagehandler.h"

ImportXmlFileValidationMessageHandler::ImportXmlFileValidationMessageHandler()
{

}

ImportXmlFileValidationMessageHandler::~ImportXmlFileValidationMessageHandler()
{

}

QString ImportXmlFileValidationMessageHandler::statusMessage() const
{
    return m_description;
}

int ImportXmlFileValidationMessageHandler::line() const
{
    return m_sourceLocation.line();
}

int ImportXmlFileValidationMessageHandler::column() const
{
    return m_sourceLocation.column();
}

void ImportXmlFileValidationMessageHandler::handleMessage(QtMsgType type,
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
