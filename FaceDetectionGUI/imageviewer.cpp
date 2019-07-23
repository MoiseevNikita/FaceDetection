#include "imageviewer.h"
#include "ui_imageviewer.h"
#include "mainwindow.h"
#include <QImage>

ImageViewer::ImageViewer(QWidget *parent, QString filename) :
    QWidget(parent),
    ui(new Ui::ImageViewer),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    QPixmap pixmap = QPixmap::fromImage(QImage(filename));
    image = new QGraphicsPixmapItem(pixmap);
    scene->addItem(image);

    ImageAnalyzer *analyzer = ImageAnalyzer::analyzeImage(filename);
    connect(analyzer, &ImageAnalyzer::finished, this, &ImageViewer::onImageAnalyzerFinished);

    // Add 'Processing...' annotation to the center of the image
    QGraphicsTextItem* processingAnnotation = scene->addText("Processing...");

    QFont font; font.setPixelSize(pixmap.width() / 10);
    processingAnnotation->setFont(font);
    processingAnnotation->setDefaultTextColor(Qt::green);

    QRectF boundRect = processingAnnotation->boundingRect();
    processingAnnotation->setPos(
        pixmap.width() / 2 - boundRect.width() / 2,
        pixmap.height() / 2 - boundRect.height() / 2
    );

    textAnnotations.push_back(processingAnnotation);
}

ImageViewer::~ImageViewer()
{
    for (QGraphicsRectItem *rect : rectangles)
        delete rect;
    for (QGraphicsTextItem *text : textAnnotations)
        delete text;

    delete image;
    delete scene;
    delete ui;
}

void ImageViewer::onImageAnalyzerFinished(std::vector<FaceData> faces)
{
    // Remove 'Processing...' annotation
    scene->removeItem(textAnnotations[0]);
    textAnnotations.clear();

    QPen pen; pen.setColor(Qt::yellow); pen.setWidth(5);

    foreach (const FaceData &face, faces) {
        QGraphicsRectItem *rect = scene->addRect(
            QRect(face.coordinates.x, face.coordinates.y, face.coordinates.width, face.coordinates.height),
            pen
        );
        rectangles.push_back(rect);

        QString gender = face.gender == FaceData::female ? "Female" : "Male";
        QGraphicsTextItem* annotation = scene->addText(
            gender + ", " + QString::number(face.age.mean, 'f', 1) + " y.o.");

        QFont font; font.setPixelSize(face.coordinates.width / 8);
        annotation->setFont(font);
        annotation->setDefaultTextColor(Qt::green);
        annotation->setPos(face.coordinates.x, face.coordinates.y);

        textAnnotations.push_back(annotation);
    }
    emit imageAnnotated();
}

