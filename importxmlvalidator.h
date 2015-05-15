#ifndef IMPORTXMLVALIDATOR_H
#define IMPORTXMLVALIDATOR_H

#include <QObject>

class ImportXmlValidator : public QObject
{
    Q_OBJECT
public:
    explicit ImportXmlValidator(QObject *parent = 0);
    ~ImportXmlValidator();

signals:

public slots:
};

#endif // IMPORTXMLVALIDATOR_H
