#include "triplet.h"

Triplet::Triplet()
{

}

Triplet::Triplet(QVariantMap &triplet_map)
{
    bool ok = false;

    this->x = triplet_map["x"].toString().toDouble(&ok);
    this->y = triplet_map["y"].toString().toDouble(&ok);
    this->z = triplet_map["z"].toString().toDouble(&ok);
}
