#ifndef ZONE_H
#define ZONE_H

#include <QMetaType>
#include <QString>
#include "shape.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

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
    vector<Point> getPoints(double xmin, double ymin);
};

Q_DECLARE_METATYPE(Zone)

#endif // ZONE_H
