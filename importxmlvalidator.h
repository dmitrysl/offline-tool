#ifndef IMPORTXMLVALIDATOR_H
#define IMPORTXMLVALIDATOR_H

#include <QObject>

#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include "exportxmlfilevalidationmessagehandler.h"

class ImportXmlValidator : public QObject
{
    Q_OBJECT
public:
    explicit ImportXmlValidator(QObject *parent = 0);
    ~ImportXmlValidator();

    void validate(const QByteArray schemaData, const QByteArray instanceData);

signals:
    void validationStatus(bool errorOccurred, const QAbstractMessageHandler messageHandler);

public slots:

private:
    bool errorOccurred;
};

#endif // IMPORTXMLVALIDATOR_H
