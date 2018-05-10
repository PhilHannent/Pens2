#include "pathgraphicsitem.h"

#include <QPen>
#include <QPainter>
#include <QDebug>

PathGraphicsItem::PathGraphicsItem()
    : m_data(nullptr)
{
    qInfo() << "PathGraphicsItem::PathGraphicsItem()";
    this->setFlag(ItemIsMovable);
}

PathGraphicsItem::~PathGraphicsItem()
{
    qInfo() << "PathGraphicsItem::~PathGraphicsItem()";
}

void PathGraphicsItem::addPoint(const PathDataPoint & point)
{
    if (m_data == nullptr)
    {
        return;
    }

    this->prepareGeometryChange();
    m_data->addPoint(point);
}

void PathGraphicsItem::setPathData(PathDataPointer data)
{
    if (m_data != nullptr)
    {
        disconnect(m_data.operator->(), &PathData::pointAdded, this, nullptr);
    }

    this->prepareGeometryChange();
    m_data = data;
    connect(m_data.operator->(), &PathData::pointAdded, this, [ = ]()
    {
        this->prepareGeometryChange();
    });
}

QRectF PathGraphicsItem::boundingRect() const
{
    if (m_data == nullptr)
    {
        return QRectF();
    }

    const qreal p = this->pen().widthF() * 0.5;
    return m_data->boundingRect() + QMarginsF(p, p, p, p);
}

QPen PathGraphicsItem::pen() const
{
    return PathData::defaultPen();
}

void PathGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (m_data == nullptr)
    {
        return;
    }

    painter->setPen(this->pen());
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(m_data->painterPath());
}
