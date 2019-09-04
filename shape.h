#ifndef SHAPE_H
#define SHAPE_H

#include <QMetaType>
#include <QList>
#include <QDebug>
#include "vertice.h"

class Shape
{
public:
    Shape();
    Shape(const Shape &oldObj);
    Shape(QVariantMap &shape_map);
    ~Shape();
    QList<Vertice> vertices;
};

Q_DECLARE_METATYPE(Shape)

#endif // SHAPE_H
