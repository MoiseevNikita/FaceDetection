#include "imageanalyzer.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

ImageAnalyzer* ImageAnalyzer::analyzeImage(QString filename)
{
    ImageAnalyzer *analyzer = new ImageAnalyzer();
    analyzer->sendRequest(filename);
    return analyzer;
}

ImageAnalyzer::ImageAnalyzer(QObject *parent) : QObject(parent)
{
    connect(&networkManager, &QNetworkAccessManager::finished, this, &ImageAnalyzer::onManagerFinished);
}

void ImageAnalyzer::sendRequest(QString filename)
{
    QNetworkRequest request(QUrl("https://backend.facecloud.tevian.ru/api/v1/detect?demographics=true"));
    request.setRawHeader("Content-Type", "image/jpeg");
    request.setRawHeader("Authorization", "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJqdGkiOiI3NzA4ZTc2NS05YjEyLTQzMjAtOTczNi0wNGU0N2NmN2ZlNGMiLCJzdWIiOjUwLCJpYXQiOjE1NjI5NTQwMDcsIm5iZiI6MTU2Mjk1NDAwNywidHlwZSI6ImFjY2VzcyIsImZyZXNoIjpmYWxzZX0.5jkM56KyCPN7I0nwgJQUi07uByX_h74ZmAqkWteOcC8");
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        networkManager.post(request, ba);
    }
}

void ImageAnalyzer::onManagerFinished(QNetworkReply *reply)
{
    QString strReply = reply->readAll();
    QJsonObject jsonObject = QJsonDocument::fromJson(strReply.toUtf8()).object();
    QJsonArray jsonArray = jsonObject["data"].toArray();

    std::vector<FaceData> faces;
    foreach (const QJsonValue& value, jsonArray) {
        QJsonObject obj = value.toObject();
        FaceData face;

        face.coordinates.x = obj["bbox"].toObject()["x"].toInt();
        face.coordinates.y = obj["bbox"].toObject()["y"].toInt();
        face.coordinates.height = obj["bbox"].toObject()["height"].toInt();
        face.coordinates.width = obj["bbox"].toObject()["width"].toInt();

        face.age.mean = obj["demographics"].toObject()["age"].toObject()["mean"].toDouble();
        face.age.variance = obj["demographics"].toObject()["age"].toObject()["variance"].toDouble();

        obj["demographics"].toObject()["gender"].toString() == "female" ?
            face.gender = FaceData::female :
            face.gender = FaceData::male;

        faces.push_back(face);
    }

    emit finished(faces);
    deleteLater();
}
