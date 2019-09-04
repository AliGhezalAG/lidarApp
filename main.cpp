#include "lidarapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LidarApp lidarApp;
    lidarApp.show();

    return a.exec();
}
