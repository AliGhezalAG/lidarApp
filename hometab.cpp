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


//    Mat image = imread("/home/nano/Documents/lidarApp/suricate.png");
    homeMap = initMap(zonePack);

    cv::Mat temp;
    cvtColor(homeMap, temp, CV_BGR2RGB);
    QImage myImage = QImage(const_cast <uchar *> (temp.data), temp.cols, temp.rows, static_cast <int>(temp.step), QImage::Format_RGB888);

    imgDisplayLabel = new QLabel("");
    imgDisplayLabel->setPixmap(QPixmap::fromImage(myImage));
    imgDisplayLabel->adjustSize();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(areaNameLayout);
    mainLayout->addLayout(areaCountLayout);
    mainLayout->addLayout(zoneListLayout);
    mainLayout->addWidget(imgDisplayLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

Mat HomeTab::initMap(ZonePacket &zonePack)
{
    xmin = 0;
    xmax = 0;
    ymin = 0;
    ymax = 0;

    for (Zone currentZone : zonePack.zones) {
        for(Vertice v : currentZone.shape.vertices){
            if(v.x > xmax)
                xmax = v.x;
            else if (v.x < xmin)
                xmin = v.x;

            if(v.y > ymax)
                ymax = v.y;
            else if (v.y < ymin)
                ymin = v.y;
        }
    }

    int x = static_cast <int>(ceil(xmax-xmin+1))*50;
    int y = static_cast <int>(ceil(ymax-ymin+1))*50;

    Mat homeMap(x, y, CV_8UC3, Scalar(0, 0, 0));

    for (Zone currentZone : zonePack.zones) {
        vector<Point> pt = currentZone.getPoints(xmin, ymin);
        polylines(homeMap,pt,true,Scalar(0,0,255),2,150,0);
    }

    return homeMap;
}

int HomeTab::getTotalCount(ZonePacket &zonePack)
{
    int count = 0;
    for (int i = 0; i < zonePack.zones.size(); i++) {
        count += zonePack.zones.at(i).objectCount;
    }
    return count;
}

void HomeTab::updateHome(ZonePacket &zonePacket, ObjectPacket &objectPack)
{
    QString totalCount = QString::number(getTotalCount(zonePacket));
    countLabel->setText(totalCount);
    countLabel->update();
    countLabel->show();

    Mat newHomeMap = homeMap.clone();
    for(Object obj : objectPack.getObjectList()){
        Mat lilImageE = imread("/home/nano/Documents/lidarApp/yellowDot.jpg");
        Size size(10,10);//the dst image size,e.g.100x100
        Mat lilImage;//dst image
        cv::resize(lilImageE,lilImage,size);
        const int x = static_cast <int>(obj.position.x - xmin + 0.5)*50;
        const int y = static_cast <int>(obj.position.y - ymin + 0.5)*50;
        if(x>0 && x + lilImage.cols < newHomeMap.cols && y>0 && y + lilImage.rows < newHomeMap.rows)
            lilImage.copyTo(newHomeMap(cv::Rect(x,y,lilImage.cols, lilImage.rows)));
    }

    cv::Mat temp;
    cvtColor(newHomeMap, temp, CV_BGR2RGB);
    QImage myImage = QImage(const_cast <uchar *> (temp.data), temp.cols, temp.rows, static_cast <int>(temp.step), QImage::Format_RGB888);
    imgDisplayLabel->setPixmap(QPixmap::fromImage(myImage));
    imgDisplayLabel->adjustSize();
    imgDisplayLabel->update();
    imgDisplayLabel->show();
}
