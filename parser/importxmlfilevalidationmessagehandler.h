#ifndef EXPORTXMLFILEVALIDATIONMESSAGEHANDLER_H
#define EXPORTXMLFILEVALIDATIONMESSAGEHANDLER_H


#include <QAbstractMessageHandler>
#include <QUrl>
#include <QtXmlPatterns/QSourceLocation>

class ImportXmlFileValidationMessageHandler : public QAbstractMessageHandler
{
public:
    ImportXmlFileValidationMessageHandler();
    ~ImportXmlFileValidationMessageHandler();

    QString statusMessage() const;
    int line() const;
    int column() const;

protected:
    virtual void handleMessage(QtMsgType type,
                               const QString &description,
                               const QUrl &identifier,
                               const QSourceLocation &sourceLocation);

private:
    QtMsgType m_messageType;
    QString m_description;
    QSourceLocation m_sourceLocation;
};

#endif // EXPORTXMLFILEVALIDATIONMESSAGEHANDLER_H
