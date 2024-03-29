#include "zoomhandler.h"
#include <QWheelEvent>

ZoomHandler::ZoomHandler(QWidget *parent) : QGraphicsView (parent)
{
}

void ZoomHandler::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.15;

    if (event->delta() > 0) {
        scale(scaleFactor, scaleFactor);
    } else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}
