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

    homeMap = initMap(zone);

    cv::Mat temp;
    cvtColor(homeMap, temp, CV_BGR2RGB);
    QImage myImage = QImage(const_cast <uchar *> (temp.data), temp.cols, temp.rows, static_cast <int>(temp.step), QImage::Format_RGB888);

    imgDisplayLabel = new QLabel("");
    imgDisplayLabel->setPixmap(QPixmap::fromImage(myImage));
    imgDisplayLabel->adjustSize();

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(zoneNameLayout);
    mainLayout->addLayout(zoneCountLayout);
    mainLayout->addLayout(zoneListLayout);
    mainLayout->addWidget(imgDisplayLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void ZoneTab::updateZone(Zone &zone, ObjectPacket &objectPack)
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

    Mat newHomeMap = homeMap.clone();
    for(Object obj : objectPack.getObjectList()){
        if(zone.objectIds.contains(obj.id)){
            Mat lilImageE = imread("/home/nano/Documents/lidarApp/yellowDot.jpg");
            Size size(10,10);//the dst image size,e.g.100x100
            Mat lilImage;//dst image
            cv::resize(lilImageE,lilImage,size);
            const int x = static_cast <int>((obj.position.x - xmin + 0.5)*50);
            const int y = static_cast <int>((obj.position.y - ymin + 0.5)*50);
            if(x>0 && x + lilImage.cols < newHomeMap.cols && y>0 && y + lilImage.rows < newHomeMap.rows)
                lilImage.copyTo(newHomeMap(cv::Rect(x,y,lilImage.cols, lilImage.rows)));

        }
    }

    cv::Mat temp;
    cvtColor(newHomeMap, temp, CV_BGR2RGB);
    QImage myImage = QImage(const_cast <uchar *> (temp.data), temp.cols, temp.rows, static_cast <int>(temp.step), QImage::Format_RGB888);
    imgDisplayLabel->setPixmap(QPixmap::fromImage(myImage));
    imgDisplayLabel->adjustSize();
    imgDisplayLabel->update();
    imgDisplayLabel->show();

    mainLayout->update();
    setLayout(mainLayout);
}



Mat ZoneTab::initMap(Zone &zone)
{
    xmin = 0;
    xmax = 0;
    ymin = 0;
    ymax = 0;

    for(Vertice v : zone.shape.vertices){
        if(v.x > xmax)
            xmax = v.x;
        else if (v.x < xmin)
            xmin = v.x;

        if(v.y > ymax)
            ymax = v.y;
        else if (v.y < ymin)
            ymin = v.y;
    }

    int x = static_cast <int>(ceil(xmax-xmin+1)*50);
    int y = static_cast <int>(ceil(ymax-ymin+1)*50);

    Mat homeMap(x, y, CV_8UC3, Scalar(0, 0, 0));

    vector<Point> pt = zone.getPoints(xmin, ymin);
    polylines(homeMap,pt,true,Scalar(0,0,255),2,150,0);

    return homeMap;
}
