#ifndef ZONETAB_H
#define ZONETAB_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "zonepacket.h"

class ZoneTab : public QWidget
{
    Q_OBJECT

public:
    ZoneTab(Zone &zone, QWidget *parent = nullptr);
    void updateZone(Zone &currentZone)
;
private:
    QString name;
    QLabel *countLabel;
    QGridLayout *zoneListLayout;
    QVBoxLayout *mainLayout;
    QLabel *nameLabel;
    QLabel *trackLabel;
};

#endif // ZONETAB_H
