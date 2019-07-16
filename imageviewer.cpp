#include "imageviewer.h"
#include "ui_imageviewer.h"
#include "mainwindow.h"
#include "facedetectionrequestsender.h"
#include <QImage>
#include <QWheelEvent>
#include <math.h>

ImageViewer::ImageViewer(QWidget *parent, const QString& file) :
    QWidget(parent),
    ui(new Ui::ImageViewer),
    filename(file),
    main_window(dynamic_cast<MainWindow*>(parent))
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QPixmap pixmap = QPixmap::fromImage(QImage(filename));
    image = new QGraphicsPixmapItem(pixmap);
    scene->addItem(image);

    // Add 'Processing...' annotation to the center of the image
    QGraphicsTextItem* processing_annotation = scene->addText("Processing...");
    text_annotations.push_back(processing_annotation);
    processing_annotation->setDefaultTextColor(Qt::green);
    QFont font;
    font.setPixelSize(pixmap.width() / 10);
    processing_annotation->setFont(font);

    QRectF bound_rect = processing_annotation->boundingRect();
    processing_annotation->setPos(
        pixmap.width() / 2 - bound_rect.width() / 2,
        pixmap.height() / 2 - bound_rect.height() / 2);


    analyzer = new FaceDetectionRequestSender(this);
    analyzer->send_request(filename);
}

ImageViewer::~ImageViewer()
{
    //TODO:
    //if (scene) delete scene;
    //if (image) delete image;
    //if (analyzer) delete analyzer;
    delete ui;
}

QString to_string(const FaceStruct::gender_t gender)
{
    return gender == FaceStruct::gender_t::female ? "Female" : "Male";
}

void ImageViewer::onImageAnalisysFinished(const std::vector<FaceStruct> &faces)
{
    QPixmap pixmap = QPixmap::fromImage(QImage(filename));
    QPainter painter(&pixmap);

    QPen pen; pen.setColor(Qt::yellow); pen.setWidth(5);
    painter.setPen(pen);

    // Remove 'Processing...' anotation
    scene->removeItem(text_annotations[0]);
    text_annotations.clear();

    foreach (const FaceStruct &face, faces) {
        painter.drawRect(QRect(face.coord_x, face.coord_y, face.coord_width, face.coord_height));

        QGraphicsTextItem* annotation = scene->addText(
                to_string(face.gender) + ", "
                + QString::number(face.age_mean, 'f', 1) + " y.o.");
        text_annotations.push_back(annotation);

        QFont font;
        font.setPixelSize(face.coord_width / 8);
        annotation->setFont(font);
        annotation->setDefaultTextColor(Qt::green);
        annotation->setPos(face.coord_x, face.coord_y);

        dynamic_cast<QGraphicsPixmapItem*>(image)->setPixmap(pixmap);
    }
    main_window->onOneImageProcessingFinished();
}
