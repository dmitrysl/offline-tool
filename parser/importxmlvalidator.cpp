#include "importxmlvalidator.h"

ImportXmlValidator::ImportXmlValidator(QObject *parent) : QObject(parent)
{
    messageHandler = new ExportXmlFileValidationMessageHandler;
}

ImportXmlValidator::~ImportXmlValidator()
{
    delete messageHandler;
}

void ImportXmlValidator::validate(const QByteArray schemaData, const QByteArray &instanceData)
{
    QXmlSchema schema;
    schema.setMessageHandler(messageHandler);

    schema.load(schemaData);

    bool errorOccurred = false;
    if (!schema.isValid())
    {
        errorOccurred = true;
    }
    else
    {
        QXmlSchemaValidator validator(schema);
        if (!validator.validate(instanceData))
            errorOccurred = true;
    }

    emit validationStatus(errorOccurred, messageHandler);
}
