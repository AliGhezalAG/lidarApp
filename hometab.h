#ifndef HOMETAB_H
#define HOMETAB_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "zonepacket.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include "triplet.h"
#include "objectpacket.h"
#include "config.h"

using namespace cv;
using namespace std;

class HomeTab : public QWidget
{
    Q_OBJECT

public:
    HomeTab(ZonePacket &zonePack, QWidget *parent = nullptr);
    void updateHome(ZonePacket &zonePacket);

private:
    int getTotalCount(ZonePacket &zonePack);
    Mat initMap(ZonePacket &zonePack);
    QLabel *countLabel;
    QLabel *zoneLabel;
    QLabel *imgDisplayLabel;
    Mat homeMap;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
};

#endif // HOMETAB_H
