
#include "qortexclient.h"

QortexClient::QortexClient(QTabWidget *tabWidget) : tabWidget(tabWidget), tabsInitiated(false)
{
    zoneSocket = new QTcpSocket(this);
    objectSocket = new QTcpSocket(this);

    connect(zoneSocket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(zoneSocket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(zoneSocket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(zoneSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    connect(objectSocket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(objectSocket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(objectSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

}

// Tentative de connexion au serveur
void QortexClient::start()
{
    zoneSocket->abort(); // On désactive les connexions précédentes s'il y en a
    zoneSocket->connectToHost("127.0.0.1", 17172); // On se connecte au serveur demandé
    objectSocket->abort(); // On désactive les connexions précédentes s'il y en a
    objectSocket->connectToHost("127.0.0.1", 17171); // On se connecte au serveur demandé
}

// On a reçu un paquet (ou un sous-paquet)
void QortexClient::donneesRecues()
{
    QByteArray zoneStream = zoneSocket->readAll();
    QByteArray objectStream = objectSocket->readAll();

    if(!zoneStream.isEmpty() && !objectStream.isEmpty())
    {
        QVariantMap root_map;

        root_map = getMapFromStream(zoneStream);
        ZonePacket *zonePack = new ZonePacket(root_map);

        root_map = getMapFromStream(objectStream);
        ObjectPacket *objectPack = new ObjectPacket(root_map);

        if(!tabsInitiated)
            initTabs(zonePack);

        updateTabs(zonePack, objectPack);
        //int count = zonePack.zones.at(0).objectCount;
        //  objectCount->setText(QString::number(count));

        //    listeMessages->append(QTextCodec::codecForMib(106)->toUnicode(packet));
    }
}

void QortexClient::initTabs(ZonePacket *zonePack)
{
    homeTab = new HomeTab(*zonePack);
    tabWidget->addTab(homeTab, tr("Home"));
    zoneTabMap = *new QMap<QString, ZoneTab *>;
    for (int i = 0; i < zonePack->zones.size(); i++) {
        Zone currentZone = zonePack->zones.at(i);
        ZoneTab *currentZoneTab = new ZoneTab(currentZone);
        tabWidget->addTab(currentZoneTab, tr(currentZone.name.toLocal8Bit().data()));
        zoneTabMap[currentZone.name] = currentZoneTab;
    }
    tabsInitiated = true;
}

void QortexClient::updateTabs(ZonePacket *zonePack, ObjectPacket *objectPack)
{
    homeTab->updateHome(*zonePack);
    for (int i = 0; i < zonePack->zones.size(); i++) {
        Zone currentZone = zonePack->zones.at(i);
        ZoneTab *currentZoneTab = zoneTabMap[currentZone.name];
        currentZoneTab->updateZone(currentZone);
    }
}

QVariantMap QortexClient::getMapFromStream(QByteArray &stream)
{
    QByteArray streamSeparator = QByteArray::fromHex("0000");

    int startIndex;
    int endIndex;
    QByteArray packet;
    QJsonDocument jsonPacket;
    QJsonObject root_obj;
    QVariantMap root_map;

    startIndex = stream.indexOf(streamSeparator)+2;
    endIndex = stream.indexOf(streamSeparator, startIndex)-2;
    packet = stream.mid(startIndex, endIndex-startIndex);
    jsonPacket = QJsonDocument::fromJson(packet);
    root_obj = jsonPacket.object();
    root_map = root_obj.toVariantMap();

    return root_map;
}

void QortexClient::processZones()
{

}

void QortexClient::connecte(){}
void QortexClient::deconnecte(){}

// Ce slot est appelé lorsqu'il y a une erreur
void QortexClient::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
    {
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "<em>ERREUR : le serveur a coupé la connexion.</em>";
        break;
    default:
        qDebug() << &"ERREUR :"  [ erreur];
    }
}
