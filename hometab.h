#ifndef HOMETAB_H
#define HOMETAB_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "zonepacket.h"

class HomeTab : public QWidget
{
    Q_OBJECT

public:
    HomeTab(ZonePacket &zonePack, QWidget *parent = nullptr);
    void updateHome(ZonePacket &zonePacket);

private:
    int getTotalCount(ZonePacket &zonePack);
    QLabel *countLabel;
    QLabel *zoneLabel;
};

#endif // HOMETAB_H
