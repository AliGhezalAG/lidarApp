#include "zonetab.h"

ZoneTab::ZoneTab(Zone &zone, QWidget *parent)
    : QWidget(parent), name(zone.name)
{
//    QHBoxLayout *zoneNameLayout = new QHBoxLayout();
//    QLabel *zoneNameLabel = new QLabel(tr("Zone name:"));
//    nameLabel = new QLabel(tr(zone.name.toLocal8Bit().data()));
//    zoneNameLayout->addWidget(zoneNameLabel);
//    zoneNameLayout->addWidget(nameLabel);

    Mat zoneCountImg = imread("/home/nano/Documents/lidarApp/images/personzoneCountImg.jpg");

    Point countDisplayPoint = Point(25, 30);
    QString countDisplay = "x" + QString::number(zone.objectCount);
    putText(zoneCountImg, countDisplay.toStdString(), countDisplayPoint,FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(0,0,0), 1, CV_AA);

    cv::Mat personIconeTemp;
    cvtColor(zoneCountImg, personIconeTemp, CV_BGR2RGB);
    QImage personIconeImage = QImage(const_cast <uchar *> (personIconeTemp.data), personIconeTemp.cols, personIconeTemp.rows, static_cast <int>(personIconeTemp.step), QImage::Format_RGB888);
    zoneCountImgDisplayLabel = new QLabel("");
    zoneCountImgDisplayLabel->setPixmap(QPixmap::fromImage(personIconeImage));

    zoneListLayout = new QGridLayout;
    QLabel *zoneListLabel = new QLabel(tr("Track list:"));
    zoneListLayout->addWidget(zoneListLabel, 0, 0, Qt::AlignTop);

    QString label = "";
    for (int i = 0; i < zone.objectIds.size(); i++) {
        label += QString::number(zone.objectIds.at(i)) + "\n";
    }
    trackLabel = new QLabel(tr(label.toLocal8Bit().data()));
    zoneListLayout->addWidget(trackLabel, 0, 1, Qt::AlignTop);

    Mat lilImage;
    //    homeMap = initMap(zone);
    if (this->name.contains("Open space 1")) {
        lilImage = imread("/home/nano/Documents/lidarApp/images/openSpace1.jpg");
    } else if (this->name.contains("Open space 2")){
        lilImage = imread("/home/nano/Documents/lidarApp/images/openSpace2.jpg");
    } else {
        lilImage = imread("/home/nano/Documents/lidarApp/images/openSpace3.jpg");
    }

    Size size(392,446);
    cv::resize(lilImage,homeMap,size);

    cv::Mat temp;
    cvtColor(homeMap, temp, CV_BGR2RGB);
    QImage myImage = QImage(const_cast <uchar *> (temp.data), temp.cols, temp.rows, static_cast <int>(temp.step), QImage::Format_RGB888);

    imgDisplayLabel = new QLabel("");
    imgDisplayLabel->setPixmap(QPixmap::fromImage(myImage));
    //    imgDisplayLabel->adjustSize();
    imgDisplayLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(15);
    mainLayout->addSpacing(100);
//    mainLayout->addLayout(zoneNameLayout);
    mainLayout->addWidget(zoneCountImgDisplayLabel);
    mainLayout->addLayout(zoneListLayout);
    mainLayout->addStretch(1);

    QHBoxLayout *finalLayout = new QHBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(imgDisplayLabel);
    setLayout(finalLayout);
}

void ZoneTab::updateZone(Zone &zone)
{

    Mat zoneCountImg = imread("/home/nano/Documents/lidarApp/images/personzoneCountImg.jpg");

    Point countDisplayPoint = Point(25, 30);
    QString countDisplay = "x" + QString::number(zone.objectCount);
    putText(zoneCountImg, countDisplay.toStdString(), countDisplayPoint,FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(0,0,0), 1, CV_AA);

    cv::Mat personIconeTemp;
    cvtColor(zoneCountImg, personIconeTemp, CV_BGR2RGB);
    QImage personIconeImage = QImage(const_cast <uchar *> (personIconeTemp.data), personIconeTemp.cols, personIconeTemp.rows, static_cast <int>(personIconeTemp.step), QImage::Format_RGB888);
    zoneCountImgDisplayLabel->setPixmap(QPixmap::fromImage(personIconeImage));
    zoneCountImgDisplayLabel->update();
    zoneCountImgDisplayLabel->show();

    //    QString count = QString::number(zone.objectCount);
    //    countLabel->setText(count);
    //    countLabel->update();
    //    countLabel->show();

    QString label = "";
    for (int i = 0; i < zone.objectIds.size(); i++) {
        label += QString::number(zone.objectIds.at(i)) + "\n";
    }
    trackLabel->setText(label);
    trackLabel->update();
    trackLabel->show();

    mainLayout->update();
}

Mat ZoneTab::initMap(Zone &zone)
{
    xmin = zone.shape.vertices.at(0).x;
    xmax = zone.shape.vertices.at(0).x;
    ymin = zone.shape.vertices.at(0).y;
    ymax = zone.shape.vertices.at(0).y;

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

    Mat homeMap(y, x, CV_8UC3, Scalar(211, 211, 211));

    vector<Point> pt = zone.getPoints();
    polylines(homeMap,pt,true,Scalar(0,0,255),2,150,0);

    return homeMap;
}
