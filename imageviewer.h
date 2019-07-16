#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QImage>
#include <vector>

class MainWindow;

class FaceDetectionRequestSender;
struct FaceStruct;

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent, const QString& file);
    ~ImageViewer();

private:
    void onImageAnalisysFinished(const std::vector<FaceStruct>&);

    Ui::ImageViewer *ui;
    QString filename;
    QGraphicsScene *scene;
    QGraphicsItem *image;
    std::vector<QGraphicsTextItem*> text_annotations;
    FaceDetectionRequestSender *analyzer;

    MainWindow* main_window;

    friend class FaceDetectionRequestSender;
};

#endif // IMAGEVIEWER_H
