#include "facedetectionrequestsender.h"
#include <QtNetwork/QNetworkRequest>
#include <QFile>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

FaceDetectionRequestSender::FaceDetectionRequestSender(ImageViewer *_parent)
    : parent(_parent)
{
    connect(&manager, &QNetworkAccessManager::finished, this, &FaceDetectionRequestSender::onManagerFinished);
}

void FaceDetectionRequestSender::send_request(const QString &filename)
{
    QNetworkRequest request(QUrl("https://backend.facecloud.tevian.ru/api/v1/detect?demographics=true"));
    request.setRawHeader("Content-Type", "image/jpeg");
    request.setRawHeader("Authorization", "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJqdGkiOiI3NzA4ZTc2NS05YjEyLTQzMjAtOTczNi0wNGU0N2NmN2ZlNGMiLCJzdWIiOjUwLCJpYXQiOjE1NjI5NTQwMDcsIm5iZiI6MTU2Mjk1NDAwNywidHlwZSI6ImFjY2VzcyIsImZyZXNoIjpmYWxzZX0.5jkM56KyCPN7I0nwgJQUi07uByX_h74ZmAqkWteOcC8");
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        manager.post(request, ba);
    }
}

void FaceDetectionRequestSender::onManagerFinished(QNetworkReply *reply)
{
    QString strReply = reply->readAll();
    QJsonObject jsonObject = QJsonDocument::fromJson(strReply.toUtf8()).object();
    QJsonArray jsonArray = jsonObject["data"].toArray();

    std::vector<FaceStruct> faces;
    foreach (const QJsonValue& value, jsonArray) {
        FaceStruct face;
        int &x = face.coord_x, &y = face.coord_y, &width = face.coord_width, &height = face.coord_height;
        double &age_mean = face.age_mean, &age_variance = face.age_variance;
        FaceStruct::gender_t &gender = face.gender;

        QJsonObject obj = value.toObject();

        age_mean = obj["demographics"].toObject()["age"].toObject()["mean"].toDouble();
        age_variance = obj["demographics"].toObject()["age"].toObject()["variance"].toDouble();

        obj["demographics"].toObject()["gender"].toString() == "female" ?
            gender = FaceStruct::gender_t::female :
            gender = FaceStruct::gender_t::male;

        x = obj["bbox"].toObject()["x"].toInt();
        y = obj["bbox"].toObject()["y"].toInt();
        height = obj["bbox"].toObject()["height"].toInt();
        width = obj["bbox"].toObject()["width"].toInt();

        faces.push_back(face);
    }
    parent->onImageAnalisysFinished(faces);
}

