#ifndef VERTICE_H
#define VERTICE_H

#include <QMetaType>
#include <QVariantMap>

class Vertice
{
public:
    Vertice();
    Vertice(const Vertice &oldObj);
    Vertice(QVariantMap &currentVertice_map);
    ~Vertice();
    double x;
    double y;
};

Q_DECLARE_METATYPE(Vertice)

#endif // VERTICE_H
