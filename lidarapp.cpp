#include "lidarapp.h"

LidarApp::LidarApp(QWidget *parent) :
    QWidget(parent)
{
    tabWidget = new QTabWidget;
    qortexClient = new QortexClient(tabWidget);

    qortexClient->start();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
    setWindowTitle(tr("Lidar App"));
}

LidarApp::~LidarApp()
{
}
