#include "resultsgenerator.h"
#include <QImage>
#include <QJsonArray>

JsonResultsGenerator::JsonResultsGenerator(QObject *parent)
    : QObject(parent)
    , imagesLeftToProcess(0)
{
}

JsonResultsGenerator::~JsonResultsGenerator()
{
    for (size_t i = 0; i < receivers.size(); ++i)
        delete receivers[i];
}

void JsonResultsGenerator::addToProcessingQueue(QString file)
{
    processingQueue.push(file);
}

void JsonResultsGenerator::startProcessing()
{
    while (!processingQueue.empty()) {
        QString file = processingQueue.front();

        AnalysisResultsReceiver *receiver = new AnalysisResultsReceiver();
        receivers.push_back(receiver);

        ++imagesLeftToProcess;
        connect(receiver, &AnalysisResultsReceiver::imageAnalyzed, this, &JsonResultsGenerator::onOneImageAnalyzed);
        receiver -> analyzeImageAndWaitForResults(file);

        processingQueue.pop();
    }
}

void JsonResultsGenerator::onOneImageAnalyzed(QString file, std::vector<FaceData> faces)
{
    QJsonArray facesArray;
    for (const FaceData& faceData : faces) {
        QJsonObject coordinates;
        coordinates.insert("x", faceData.coordinates.x);
        coordinates.insert("y", faceData.coordinates.y);
        coordinates.insert("width", faceData.coordinates.width);
        coordinates.insert("height", faceData.coordinates.height);

        QJsonObject age;
        age.insert("mean", faceData.age.mean);
        age.insert("variance", faceData.age.variance);

        QJsonObject face;
        face.insert("coordinates", coordinates);
        face.insert("age", age);
        face.insert("gender", faceData.gender == FaceData::female ? "female" : "male");
        facesArray.push_back(face);
    }
    jsonResult.insert(file, facesArray);

    --imagesLeftToProcess;
    if (!imagesLeftToProcess) {
        emit finished(jsonResult);
    }
}
