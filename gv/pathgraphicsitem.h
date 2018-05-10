#ifndef PATHGRAPHICSITEM_H
#define PATHGRAPHICSITEM_H

#include <QGraphicsObject>

#include "pathdata.h"

class PathGraphicsItem : public QGraphicsObject
{

    public:

        PathGraphicsItem();
        ~PathGraphicsItem() override;

        void    addPoint(const PathDataPoint & point);
        void    setPathData(PathDataPointer data);

        QRectF  boundingRect() const override;

        QPen    pen() const;

    protected:

        void    paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;

    private:

        PathDataPointer m_data;
};

#endif // PATHGRAPHICSITEM_H
