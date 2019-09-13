#ifndef ZONETAB_H
#define ZONETAB_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "zonepacket.h"
#include "objectpacket.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <QSizePolicy>

using namespace cv;
using namespace std;

class ZoneTab : public QWidget
{
    Q_OBJECT

public:
    ZoneTab(Zone &zone, QWidget *parent = nullptr);
    void updateZone(Zone &currentZone);

private:
    QString name;
    QLabel *countLabel;
    QGridLayout *zoneListLayout;
    QVBoxLayout *mainLayout;
    QLabel *nameLabel;
    QLabel *trackLabel;
    QLabel *imgDisplayLabel;
    QLabel  *zoneCountImgDisplayLabel;
    Mat homeMap;
    Mat initMap(Zone &zone);
    double xmin;
    double xmax;
    double ymin;
    double ymax;
};

#endif // ZONETAB_H
