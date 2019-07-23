#include "resultsgenerator.h"
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QImage>
#include <QTextStream>

int main(int argc, char *argv[])
{
    if (argc == 1 || (argc == 2 && (QString(argv[1]) == "-h" || QString(argv[1]) == "--help"))) {
        QTextStream(stdout) << "Usage: '" << argv[0] << " IMAGE [IMAGE [...]]'"
        << ", where IMAGE is a path to an image file in JPEG or BMP format.\n";
        return 0;
    }

    JsonResultsGenerator resultsGenerator;
    bool needToProcessImages = false;

    for (int i = 1; i < argc; ++i) {
        QString file = argv[i];
        QImage image;
        bool valid = image.load(file);
        if (valid) {
            resultsGenerator.addToProcessingQueue(file);
            needToProcessImages = true;
        }
    }

    QJsonObject jsonResult;
    if (needToProcessImages) {
        QCoreApplication a(argc, argv);

        QObject::connect(
            &resultsGenerator,
            &JsonResultsGenerator::finished,
            [&jsonResult](QJsonObject receivedJson) {
                jsonResult = receivedJson;
                emit QCoreApplication::quit();
            }
        );
        resultsGenerator.startProcessing();

        a.exec();
    }

    QString jsonString = QJsonDocument(jsonResult).toJson(QJsonDocument::Indented);
    QTextStream(stdout) << jsonString;

    return 0;
}
