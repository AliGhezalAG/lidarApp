#ifndef ZONE_H
#define ZONE_H

#include <QMetaType>
#include <QString>
#include "shape.h"

class Zone
{
public:
    Zone();
    Zone(const Zone &oldObj);
    Zone(QString name, int objectCount, QList<int>  objectIds);
    Zone(QVariantMap &zone_map);
    ~Zone();
    QString     uuid;
    int         timestamp;
    QString     name;
    Shape       shape;
    int         objectCount;
    QList<int>  objectIds;
    double      zMin;
    double      zMax;
    QString     zoneClass;
};

Q_DECLARE_METATYPE(Zone)

#endif // ZONE_H
