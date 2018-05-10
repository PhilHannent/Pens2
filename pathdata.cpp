#include "pathdata.h"

#include <QDebug>

PathData::PathData()
    : m_dirty(true)
{
    qInfo() << "PathData::PathData()";
}

PathData::~PathData()
{
    qInfo() << "PathData::~PathData()";
}

QRectF PathData::boundingRect() const
{
    this->updateInner();
    return m_bounding;
}

QRectF PathData::controlBoundingRect() const
{
    this->updateInner();
    return m_controlBounding;
}

QPainterPath PathData::painterPath() const
{
    return m_path;
}

void PathData::addPoint(const PathDataPoint & point)
{
    m_dataPoints.append(point);
    m_dirty = true;
    emit this->pointAdded();
}

QVector<PathDataPoint> PathData::data() const
{
    return m_dataPoints;
}

QPen PathData::defaultPen()
{
    QPen pen(Qt::black);
    pen.setWidthF(5.0);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    return pen;
}

void PathData::updateInner() const
{
    if (!m_dirty)
    {
        return;
    }

    m_dirty = false;

    m_path = QPainterPath();

    for (const PathDataPoint & p : qAsConst(m_dataPoints))
    {
        switch (p.type)
        {
            case p.Move:
            {
                m_path.moveTo(p.x, p.y);
                break;
            }

            case p.Line:
            {
                m_path.lineTo(p.x, p.y);
                break;
            }
        }
    }

    m_controlBounding = m_path.controlPointRect();
    m_bounding = m_path.boundingRect();
}
