#include "vertice.h"

Vertice::Vertice()
{

}

Vertice::Vertice(const Vertice &oldObj)
{
    this->x = oldObj.x;
    this->y = oldObj.y;
}

Vertice::Vertice(QVariantMap &currentVertice_map)
{
    this->x = currentVertice_map["x"].toDouble();
    this->y = currentVertice_map["y"].toDouble();
}

Vertice::~Vertice()
{

}
