#include "hometab.h"

HomeTab::HomeTab(ZonePacket &zonePack, QWidget *parent)
    : QWidget(parent)
{
    homeMap = initMap(zonePack);

    cv::Mat temp;
    cvtColor(homeMap, temp, CV_BGR2RGB);
    QImage myImage = QImage(const_cast <uchar *> (temp.data), temp.cols, temp.rows, static_cast <int>(temp.step), QImage::Format_RGB888);

    imgDisplayLabel = new QLabel("");
    imgDisplayLabel->setPixmap(QPixmap::fromImage(myImage));
    imgDisplayLabel->adjustSize();

    QHBoxLayout *finalLayout = new QHBoxLayout();
    finalLayout->addWidget(imgDisplayLabel);
    setLayout(finalLayout);
}

Mat HomeTab::initMap(ZonePacket &zonePack)
{

    xmin = zonePack.zones.at(0).shape.vertices.at(0).x;
    xmax = zonePack.zones.at(0).shape.vertices.at(0).x;
    ymin = zonePack.zones.at(0).shape.vertices.at(0).y;
    ymax = zonePack.zones.at(0).shape.vertices.at(0).y;

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

    Mat originalHomeMap = imread(LOCATION_MAP_IMG);
    Size size(LOCATION_MAP_HOMETAB_SIZE_X,LOCATION_MAP_HOMETAB_SIZE_Y);
    Mat homeMap;//dst image
    cv::resize(originalHomeMap,homeMap,size);
    Mat finalHomeMap = homeMap.clone();

    for (Zone currentZone : zonePack.zones) {
        try {
            vector<Point> pt = currentZone.getPoints();
            polylines(homeMap,pt,true,Scalar(0,120,0),2,150,0);
            Point barycentre = currentZone.getDisplayPoint();
            int baseline = 0;
            int thickness = 1;
            double scale = 0.5;
            Scalar color = Scalar(0, 214, 243);
            Size textSize = getTextSize(currentZone.name.toStdString(), FONT_HERSHEY_TRIPLEX, scale, thickness, &baseline);
            baseline += thickness;
            Mat texImg(textSize.height+5, textSize.width+11, CV_8UC3, color);

            // center the text
            Point textOrg((texImg.cols - textSize.width)/2, (texImg.rows + textSize.height)/2);

            // draw the box
            rectangle(texImg, textOrg + Point(0, baseline), textOrg + Point(textSize.width, -textSize.height), color);

            // then put the text itself
            putText(texImg, currentZone.name.toStdString(), textOrg, FONT_HERSHEY_TRIPLEX, scale, Scalar::all(255),thickness, 8);

            texImg.copyTo(homeMap(cv::Rect(barycentre.x,barycentre.y,texImg.cols, texImg.rows)));
            addWeighted(homeMap, 0.6, finalHomeMap, 0.4, 0, finalHomeMap);
        } catch (Exception e) {
            qInfo() << "Exception";
        }

    }

    return finalHomeMap;
}

int HomeTab::getTotalCount(ZonePacket &zonePack)
{
    int count = 0;
    for (int i = 0; i < zonePack.zones.size(); i++) {
        count += zonePack.zones.at(i).objectCount;
    }
    return count;
}

void HomeTab::updateHome(ZonePacket &zonePacket)
{
    Mat originalHomeMap = imread(LOCATION_MAP_IMG);
    Size size(LOCATION_MAP_HOMETAB_SIZE_X,LOCATION_MAP_HOMETAB_SIZE_Y);
    Mat homeMap;
    cv::resize(originalHomeMap,homeMap,size);
    Mat newHomeMap = homeMap.clone();
    Mat finalHomeMap = homeMap.clone();

    int baseline = 0;
    int thickness = 1;
    double scale = 0.5;
    Scalar color;

    for (Zone currentZone : zonePacket.zones) {
        vector<Point> pt = currentZone.getPoints();
        if(currentZone.objectCount > 0){
            polylines(homeMap,pt,true,Scalar(0,0,255),2,150,0);
            color = Scalar(0, 0, 243);
        } else {
            polylines(homeMap,pt,true,Scalar(0,120,0),2,150,0);
            color = Scalar(0, 214, 243);
        }

        Point barycentre = currentZone.getDisplayPoint();

        Size textSize = getTextSize(currentZone.name.toStdString(), FONT_HERSHEY_COMPLEX_SMALL, scale, thickness, &baseline);
        baseline += thickness;
        Mat texImg(textSize.height+15, textSize.width+10, CV_8UC3, color);

        // center the text
        Point textOrg((texImg.cols - textSize.width)/2, (texImg.rows + textSize.height)/2);

        // draw the box
        rectangle(texImg, textOrg + Point(0, baseline), textOrg + Point(textSize.width, -textSize.height), color);

        // then put the text itself
        putText(texImg, currentZone.name.toStdString(), textOrg, FONT_HERSHEY_COMPLEX_SMALL, scale, Scalar::all(255),thickness, 8);

        texImg.copyTo(homeMap(cv::Rect(barycentre.x,barycentre.y,texImg.cols, texImg.rows)));
    }
    addWeighted(homeMap, 0.8, finalHomeMap, 0.2, 0, finalHomeMap);

    cv::Mat temp;
    cvtColor(finalHomeMap, temp, CV_BGR2RGB);
    QImage myImage = QImage(const_cast <uchar *> (temp.data), temp.cols, temp.rows, static_cast <int>(temp.step), QImage::Format_RGB888);
    imgDisplayLabel->setPixmap(QPixmap::fromImage(myImage));
    imgDisplayLabel->adjustSize();
    imgDisplayLabel->update();
    imgDisplayLabel->show();
}
