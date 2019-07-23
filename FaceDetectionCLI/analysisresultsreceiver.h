#ifndef ANALYSISRESULTSRECEIVER_H
#define ANALYSISRESULTSRECEIVER_H

#include "imageanalyzer.h"
#include <QObject>
#include <QString>

class AnalysisResultsReceiver : public QObject
{
    Q_OBJECT
public:
    explicit AnalysisResultsReceiver(QObject *parent = nullptr);
    void analyzeImageAndWaitForResults(const QString& filename);

signals:
    void imageAnalyzed(QString, std::vector<FaceData>);
public slots:
    void onImageAnalyzerFinished(std::vector<FaceData>);

private:
    QString mFilename;
};

#endif // ANALYSISRESULTSRECEIVER_H
