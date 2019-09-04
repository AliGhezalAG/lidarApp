#include "hometab.h"

HomeTab::HomeTab(ZonePacket &zonePack, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *areaNameLayout = new QHBoxLayout();
    QLabel *areaNameLabel = new QLabel(tr("Area Name:"));
    QLabel *nameLabel = new QLabel(tr("Test area"));
    areaNameLayout->addWidget(areaNameLabel);
    areaNameLayout->addWidget(nameLabel);

    QHBoxLayout *areaCountLayout = new QHBoxLayout();
    QLabel *areaCountLabel = new QLabel(tr("Area count:"));
    QString totalCount = QString::number(getTotalCount(zonePack));
    countLabel = new QLabel(tr(totalCount.toLocal8Bit().data()));
    areaCountLayout->addWidget(areaCountLabel);
    areaCountLayout->addWidget(countLabel);

    QGridLayout *zoneListLayout = new QGridLayout;
    QLabel *zoneListLabel = new QLabel(tr("Zone list:"));
    zoneListLayout->addWidget(zoneListLabel, 0, 0, Qt::AlignTop);

    QString label = "";
    for (int i = 0; i < zonePack.zones.size(); i++) {
        label += zonePack.zones.at(i).name + "\n";
    }
    zoneLabel = new QLabel(tr(label.toLocal8Bit().data()));
    zoneListLayout->addWidget(zoneLabel, 0, 1, Qt::AlignTop);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(areaNameLayout);
    mainLayout->addLayout(areaCountLayout);
    mainLayout->addLayout(zoneListLayout);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

int HomeTab::getTotalCount(ZonePacket &zonePack)
{
    int count = 0;
    for (int i = 0; i < zonePack.zones.size(); i++) {
        count += zonePack.zones.at(i).objectCount;
    }
    return count;
}

void HomeTab::updateHome(ZonePacket &zonePacket)
{
    QString totalCount = QString::number(getTotalCount(zonePacket));
    countLabel->setText(totalCount);
    countLabel->update();
    countLabel->show();
}
