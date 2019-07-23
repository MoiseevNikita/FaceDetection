#ifndef RESULTSGENERATOR_H
#define RESULTSGENERATOR_H

#include "imageanalyzer.h"
#include "analysisresultsreceiver.h"
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <vector>
#include <queue>

class JsonResultsGenerator : public QObject
{
    Q_OBJECT
public:
    explicit JsonResultsGenerator(QObject *parent = nullptr);
    ~JsonResultsGenerator();
    void addToProcessingQueue(QString file);
    void startProcessing();

signals:
    void finished(QJsonObject);
public slots:
    void onOneImageAnalyzed(QString, std::vector<FaceData>);

private:
    QJsonObject jsonResult;
    unsigned imagesLeftToProcess;
    std::queue<QString> processingQueue;
    std::vector<AnalysisResultsReceiver*> receivers;
};

#endif // RESULTSGENERATOR_H
