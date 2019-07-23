#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include <vector>
#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QtGlobal>

#if defined(BUILDING_SHARED_LIBRARY)
#  define FACEDETECTIONLIB_EXPORT Q_DECL_EXPORT
#else
#  define FACEDETECTIONLIB_EXPORT Q_DECL_IMPORT
#endif

struct FaceData {
    struct {
        int x, y, width, height;
    } coordinates;
    struct {
        double mean, variance;
    } age;
    enum {female, male} gender;
};

class FACEDETECTIONLIB_EXPORT ImageAnalyzer : public QObject
{
    Q_OBJECT

public:
    static ImageAnalyzer* analyzeImage(QString filename);

signals:
     void finished(std::vector<FaceData>);

private slots:
    void onManagerFinished(QNetworkReply *reply);

private:
    explicit ImageAnalyzer(QObject *parent = nullptr);
    void sendRequest(QString filename);

    QNetworkAccessManager networkManager;
};

#endif // IMAGEANALYZER_H
