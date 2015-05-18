#ifndef TESSTCLASS_H
#define TESSTCLASS_H

#include <QObject>

class TesstClass : public QObject
{
    Q_OBJECT
public:
    explicit TesstClass(QObject *parent = 0);
    ~TesstClass();

signals:

public slots:
};

#endif // TESSTCLASS_H
