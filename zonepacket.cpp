#include "zonepacket.h"

ZonePacket::ZonePacket()
{

}

ZonePacket::ZonePacket(QVariantMap &packet_map)
{
    QVariant currentHeader = packet_map["header"];
    QVariantMap header_map = currentHeader.value<QVariantMap>();
    this->header = *new Header(header_map);

    QVariantList zone_list = packet_map["zones"].toList();
    QVariant currentZone;
    QVariantMap zone_map;

    for (int i = 0; i < zone_list.size(); i++) {
        currentZone = zone_list.at(i);
        zone_map = currentZone.value<QVariantMap>();
        Zone myZone = *new Zone(zone_map);
        this->zones.append(myZone);
    }
}

ZonePacket::~ZonePacket()
{

}
