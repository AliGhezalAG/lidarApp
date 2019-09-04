#include "object.h"

Object::Object()
{

}

Object::Object(QVariantMap &object_map)
{
    this->id = object_map["id"].toInt();
    this->timestamp = object_map["timestamp"].toInt();
    this->objectClass = object_map["objectClass"].toString();

    QVariant currentPosition = object_map["position"];
    QVariantMap position_map = currentPosition.value<QVariantMap>();
    this->position = *new Triplet(position_map);

    QVariant currentSize = object_map["size"];
    QVariantMap size_map = currentSize.value<QVariantMap>();
    this->size = *new Triplet(size_map);

    QVariant currentVelocity = object_map["velocity"];
    QVariantMap velocity_map = currentVelocity.value<QVariantMap>();
    this->velocity = *new Triplet(velocity_map);
}
