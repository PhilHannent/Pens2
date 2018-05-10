#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget * parent)
    : QGraphicsView(parent)
{
    this->init();
}

GraphicsView::GraphicsView(QGraphicsScene * scene, QWidget * parent)
    : QGraphicsView(scene, parent)
{
    this->init();
}

void GraphicsView::resizeEvent(QResizeEvent *)
{
    QRectF rect = this->mapToScene(this->viewport()->geometry()).boundingRect();
    rect.moveTopLeft(QPointF(0, 0));
    this->scene()->setSceneRect(rect);
}

void GraphicsView::init()
{
    this->setAttribute(Qt::WA_AcceptTouchEvents);
    this->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}
