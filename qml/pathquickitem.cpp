#include "pathquickitem.h"

#include <QPainter>
#include <QDebug>

PathQuickItem::PathQuickItem()
{
    //qInfo() << "PathQuickItem::PathQuickItem()";
}

PathQuickItem::~PathQuickItem()
{
    //qInfo() << "PathQuickItem::~PathQuickItem()";
}

PathDataWeakPointer PathQuickItem::data() const
{
    return m_data.toWeakRef();
}

void PathQuickItem::setData(const PathDataWeakPointer & data)
{
    if (m_data)
    {
        disconnect(m_data.operator->(), &PathData::pointAdded, this, nullptr);
    }

    m_data = data.toStrongRef();

    auto initUpdate = [ = ]()
    {
        const qreal p = PathData::defaultPen().widthF();
        QRectF br = m_data->boundingRect() + QMarginsF(p, p, p, p);

        this->setPosition(br.topLeft());
        this->setWidth(br.width());
        this->setHeight(br.height());

        this->update();
    };

    connect(m_data.operator->(), &PathData::pointAdded, this, [ = ]()
    {
        initUpdate();
    });
    initUpdate();
}

void PathQuickItem::paint(QPainter * painter)
{
    painter->setPen(PathData::defaultPen());
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(-this->position()); // paint in local coordinates
    painter->drawPath(m_data->painterPath());
}
