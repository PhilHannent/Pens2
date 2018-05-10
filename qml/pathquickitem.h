#ifndef PATHQUICKITEM_H
#define PATHQUICKITEM_H

#include <QQuickPaintedItem>

#include "pathdata.h"

class PathQuickItem : public QQuickPaintedItem
{
        Q_OBJECT

        Q_PROPERTY(PathDataWeakPointer data READ data WRITE setData)

    public:

        PathQuickItem();
        virtual ~PathQuickItem() override;

        PathDataWeakPointer data() const;
        void setData(const PathDataWeakPointer & data);

        void        paint(QPainter * painter) override;

    private:

        PathDataPointer m_data;
};

#endif // PATHQUICKITEM_H
