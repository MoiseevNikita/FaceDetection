#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include <QObject>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QString>
#include <vector>
#include "imageviewer.h"

struct FaceStruct {
    int coord_x, coord_y, coord_width, coord_height;
    double age_mean, age_variance;
    enum class gender_t {female, male} gender;
};

typedef void(&callback_func_t)(const std::vector<FaceStruct>);

class FaceDetectionRequestSender : public QObject
{
public:
    FaceDetectionRequestSender(ImageViewer *_parent);
    void send_request(const QString &filename);
private slots:
    void onManagerFinished(QNetworkReply *reply);
private:
    ImageViewer *parent;
    QNetworkAccessManager manager;
};

#endif // IMAGEANALYZER_H
