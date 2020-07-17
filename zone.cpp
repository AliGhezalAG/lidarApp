#include "zone.h"

Zone::Zone()
{

}

Zone::Zone(const Zone &oldObj)
{
    this->name = oldObj.name;
    this->uuid = oldObj.uuid;
    this->zMax = oldObj.zMax;
    this->zMin = oldObj.zMin;
    this->shape = oldObj.shape;
    this->objectIds = oldObj.objectIds;
    this->timestamp = oldObj.timestamp;
    this->zoneClass = oldObj.zoneClass;
    this->objectCount = oldObj.objectCount;
}

Zone::Zone(QString name, int objectCount, QList<int>  objectIds)
{
    this->name = name;
    this->objectIds = objectIds;
    this->objectCount = objectCount;
}

Zone::Zone(QVariantMap &zone_map)
{
    this->name = zone_map["name"].toString();
    this->objectCount = zone_map["objectCount"].toInt();

    QVariantList objectIdsList = zone_map["objectIds"].value<QVariantList>();
    this->objectIds = {};
    for (int i = 0; i < objectIdsList.size() ; i++) {
        this->objectIds.append(objectIdsList.at(i).value<int>());
    }
    this->uuid = zone_map["uuid"].toString();
    this->zMax = zone_map["zMax"].toDouble();
    this->zMin = zone_map["zMin"].toDouble();
    this->timestamp = zone_map["timestamp"].toInt();
    this->zoneClass = zone_map["zoneClass"].toString();
    QVariant currentShape = zone_map["shape"];
    QVariantMap shape_map = currentShape.value<QVariantMap>();
    this->shape = *new Shape(shape_map);
    displayPoint = Point(0,0);
}

vector<Point> Zone::getPoints()
{
    vector<Point> pt;
    for (int i=0; i<shape.vertices.size(); i++) {
        int x = static_cast <int>((shape.vertices.at(i).x+LIDAR_POS_X)*LOCATION_TO_MAP_SCALE);
        int y = static_cast <int>((shape.vertices.at(i).y+LIDAR_POS_Y)*LOCATION_TO_MAP_SCALE);
        pt.push_back(Point (x,y));
    }

    return pt;
}

Point Zone::getDisplayPoint()
{
    if(displayPoint.x == 0 && displayPoint.y == 0)
        computeDisplayPoint();

    return displayPoint;
}

void Zone::computeDisplayPoint(){
    double xmin = this->shape.vertices.at(0).x;
    double xmax = this->shape.vertices.at(0).x;
    double ymin = this->shape.vertices.at(0).y;
    double ymax = this->shape.vertices.at(0).y;

    for(Vertice v : this->shape.vertices){
        if(v.x > xmax)
            xmax = v.x;
        else if (v.x < xmin)
            xmin = v.x;

        if(v.y > ymax)
            ymax = v.y;
        else if (v.y < ymin)
            ymin = v.y;
    }

    int x = static_cast <int>(ceil(xmin+LIDAR_POS_X)*LOCATION_TO_MAP_SCALE);
    int y = static_cast <int>(ceil((ymin)+LIDAR_POS_Y)*LOCATION_TO_MAP_SCALE)-50;

    displayPoint = Point(x,y);
}

Zone::~Zone(){}
