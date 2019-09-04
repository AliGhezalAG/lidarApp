#ifndef OBJECT_H
#define OBJECT_H

#include <QMetaType>
#include <QVariantMap>
#include <QString>
#include "triplet.h"

class Object
{
public:
    Object();
    Object(QVariantMap &object_map);

private:
    int     id;
    int     timestamp;
    Triplet position;
    Triplet size;
    Triplet velocity;
    QString objectClass;
};

#endif // OBJECT_H
