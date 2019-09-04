#ifndef ZONEPACKET_H
#define ZONEPACKET_H

#include <QMetaType>
#include <QVariantMap>
#include "header.h"
#include "zone.h"

class ZonePacket
{
public:
    ZonePacket();
    ZonePacket(QVariantMap &packet_map);
    ~ZonePacket();
    Header      header;
    QList<Zone> zones;
};

Q_DECLARE_METATYPE(ZonePacket)

#endif // ZONEPACKET_H
