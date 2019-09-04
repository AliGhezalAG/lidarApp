#include "zonetab.h"

ZoneTab::ZoneTab(Zone &zone, QWidget *parent)
    : QWidget(parent), name(zone.name)
{
    QHBoxLayout *zoneNameLayout = new QHBoxLayout();
    QLabel *zoneNameLabel = new QLabel(tr("Zone name:"));
    nameLabel = new QLabel(tr(zone.name.toLocal8Bit().data()));
    zoneNameLayout->addWidget(zoneNameLabel);
    zoneNameLayout->addWidget(nameLabel);

    QHBoxLayout *zoneCountLayout = new QHBoxLayout();
    QLabel *zoneCountLabel = new QLabel(tr("Zone count:"));
    QString count = QString::number(zone.objectCount);
    countLabel = new QLabel(tr(count.toLocal8Bit().data()));
    zoneCountLayout->addWidget(zoneCountLabel);
    zoneCountLayout->addWidget(countLabel);

    zoneListLayout = new QGridLayout;
    QLabel *zoneListLabel = new QLabel(tr("Track list:"));
    zoneListLayout->addWidget(zoneListLabel, 0, 0, Qt::AlignTop);

    QString label = "";
    for (int i = 0; i < zone.objectIds.size(); i++) {
        label += QString::number(zone.objectIds.at(i)) + "\n";
    }
    trackLabel = new QLabel(tr(label.toLocal8Bit().data()));
    zoneListLayout->addWidget(trackLabel, 0, 1, Qt::AlignTop);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(zoneNameLayout);
    mainLayout->addLayout(zoneCountLayout);
    mainLayout->addLayout(zoneListLayout);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void ZoneTab::updateZone(Zone &zone)
{
    QString count = QString::number(zone.objectCount);
    countLabel->setText(count);
    countLabel->update();
    countLabel->show();

    QString label = "";
    for (int i = 0; i < zone.objectIds.size(); i++) {
        label += QString::number(zone.objectIds.at(i)) + "\n";
    }
    trackLabel->setText(label);
    trackLabel->update();
    trackLabel->show();

    mainLayout->update();
    setLayout(mainLayout);
}
