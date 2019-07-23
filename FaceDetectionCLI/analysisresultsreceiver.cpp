#include "analysisresultsreceiver.h"

AnalysisResultsReceiver::AnalysisResultsReceiver(QObject *parent) : QObject(parent)
{
}

void AnalysisResultsReceiver::analyzeImageAndWaitForResults(const QString &filename)
{
    mFilename = filename;

    ImageAnalyzer *analyzer = ImageAnalyzer::analyzeImage(filename);
    connect(analyzer, &ImageAnalyzer::finished, this, &AnalysisResultsReceiver::onImageAnalyzerFinished);
}

void AnalysisResultsReceiver::onImageAnalyzerFinished(std::vector<FaceData> faces)
{
    emit imageAnalyzed(mFilename, faces);
}
