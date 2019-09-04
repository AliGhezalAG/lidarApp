#ifndef HEADER_H
#define HEADER_H

#include <QMetaType>
#include <QString>
#include <QVariantMap>

class Header
{
public:
    Header();
    Header(const Header &oldObj);
    Header(QVariantMap &header_map);
    ~Header();
    QString     timestamp;
    QString     frameId;
    QString     sequence;
};

Q_DECLARE_METATYPE(Header)

#endif // HEADER_H
