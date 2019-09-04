#ifndef LIDARAPP_H
#define LIDARAPP_H

#include <QDialog>
#include <QTabWidget>
#include <QVBoxLayout>
#include "qortexclient.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFileInfo;
class QTabWidget;
QT_END_NAMESPACE

class LidarApp : public QWidget
{
    Q_OBJECT

public:
    explicit LidarApp(QWidget *parent = nullptr);
    ~LidarApp();

private:
    QTabWidget *tabWidget;
    QortexClient *qortexClient;
};

#endif // LIDARAPP_H
