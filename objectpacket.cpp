#include "objectpacket.h"

ObjectPacket::ObjectPacket()
{

}

ObjectPacket::ObjectPacket(QVariantMap &packet_map)
{
    QVariant currentHeader = packet_map["header"];
    QVariantMap header_map = currentHeader.value<QVariantMap>();
    this->header = *new Header(header_map);

    QVariantList object_list = packet_map["object"].toList();
    QVariant currentObject;
    QVariantMap object_map;

    for (int i = 0; i < object_list.size(); i++) {
        currentObject = object_list.at(i);
        object_map = currentObject.value<QVariantMap>();
        Object myObject = *new Object(object_map);
        this->objectList.append(myObject);
    }
}
