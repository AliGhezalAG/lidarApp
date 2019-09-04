#ifndef TRIPLET_H
#define TRIPLET_H

#include <QMetaType>
#include <QVariantMap>

class Triplet
{
public:
    Triplet();
    Triplet(QVariantMap &triplet_map);

private:
    double x;
    double y;
    double z;
};

#endif // TRIPLET_H
