#ifndef OBJECTPACKET_H
#define OBJECTPACKET_H

#include <QMetaType>
#include <QVariantMap>
#include "header.h"
#include "object.h"

class ObjectPacket
{
public:
    ObjectPacket();
    ObjectPacket(QVariantMap &packet_map);

private:
    Header          header;
    QList<Object>   objectList;
};

Q_DECLARE_METATYPE(ObjectPacket)

#endif // OBJECTPACKET_H
