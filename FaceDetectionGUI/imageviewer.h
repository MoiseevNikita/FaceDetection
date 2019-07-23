#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "imageanalyzer.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <vector>

class MainWindow;

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent, QString file);
    ~ImageViewer();

public slots:
    void onImageAnalyzerFinished(std::vector<FaceData>);
signals:
    void imageAnnotated();

private:
    Ui::ImageViewer *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *image;

    std::vector<QGraphicsRectItem*> rectangles;
    std::vector<QGraphicsTextItem*> textAnnotations;
};

#endif // IMAGEVIEWER_H
