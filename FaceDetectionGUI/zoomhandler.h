#ifndef ZOOMHANDLER_H
#define ZOOMHANDLER_H

#include <QGraphicsView>

class ZoomHandler : public QGraphicsView
{
public:
    ZoomHandler(QWidget *parent);
protected:
    virtual void wheelEvent(QWheelEvent *event);
};

#endif // ZOOMHANDLER_H
