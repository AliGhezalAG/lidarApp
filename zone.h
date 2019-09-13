#ifndef ZONE_H
#define ZONE_H

#include <QMetaType>
#include <QString>
#include "shape.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>

#define X_MIN = -12.5
#define Y_MIN = -12.25

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
    vector<Point> getPoints();
    Point getDisplayPoint();
    void computeDisplayPoint();
    Point displayPoint;
};

Q_DECLARE_METATYPE(Zone)

#endif // ZONE_H
