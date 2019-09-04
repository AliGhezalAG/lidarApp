#include "shape.h"

Shape::Shape()
{

}

Shape::Shape(const Shape &oldObj)
{
    this->vertices = oldObj.vertices;
}

Shape::Shape(QVariantMap &shape_map)
{
    QVariant currentVertices = shape_map["vertices"];
    QVariantList vertice_map = currentVertices.value<QVariantList>();
    this->vertices = {};
    for (int i = 0; i < vertice_map.size(); i++) {
        QVariant currentVertice = vertice_map.at(i);
        QVariantMap currentVertice_map = currentVertice.value<QVariantMap>();
        Vertice vertice = *new Vertice(currentVertice_map);
        this->vertices.append(vertice);
    }
}

Shape::~Shape()
{

}
