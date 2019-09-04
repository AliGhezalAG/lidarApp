#ifndef HEADER_QORTEXCLIENT
#define HEADER_QORTEXCLIENT

#include <QtWidgets>
#include <QtNetwork>
#include <QObject>
#include "zonepacket.h"
#include "objectpacket.h"
#include "hometab.h"
#include "zonetab.h"
#include "zone.h"


class QortexClient : public QWidget
{
    Q_OBJECT

public:
    QortexClient(QTabWidget *tabWidget);
    void start();

private slots:
    void donneesRecues();
    void erreurSocket(QAbstractSocket::SocketError erreur);
    void connecte();
    void deconnecte();

private:
    QTcpSocket                  *zoneSocket;
    QTcpSocket                  *objectSocket;
    ZonePacket                  zonePacket;
    ObjectPacket                objectPacket;
    QTabWidget                  *tabWidget;
    bool                        tabsInitiated;
    QMap<QString, ZoneTab *>    zoneTabMap;
    HomeTab                     *homeTab;
    void processZones();
    void initTabs(ZonePacket *zonePack);
    void updateTabs(ZonePacket *zonePack, ObjectPacket *objectPack);
    QVariantMap getMapFromStream(QByteArray &stream);

signals:
    void countingProcessingEnded();
};

#endif
