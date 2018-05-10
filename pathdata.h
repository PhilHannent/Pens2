#ifndef PATHDATA_H
#define PATHDATA_H

#include <QVector>
#include <QRectF>
#include <QPainterPath>
#include <QVector2D>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QPen>

class PathDataPoint
{
    public:

        enum Type
        {
            Move,
            Line
        };

        qreal x;
        qreal y;
        qreal pressure;
        qreal rotation;
        qint64 timestamp;
        QSizeF area;
        QVector2D velocity;
        Type type;
};

class PathData : public QObject
{
        Q_OBJECT

    public:

        PathData();
        ~PathData();

        QRectF              boundingRect() const;
        QRectF              controlBoundingRect() const;

        QPainterPath        painterPath() const;

        void                addPoint(const PathDataPoint & point);

        QVector<PathDataPoint> data() const;

        static QPen         defaultPen();

    signals:

        void                pointAdded();

    private:

        void                updateInner() const;

        QVector<PathDataPoint> m_dataPoints;

        mutable QPainterPath m_path;
        mutable QRectF      m_bounding;
        mutable QRectF      m_controlBounding;

        mutable bool        m_dirty;
};

typedef QSharedPointer<PathData> PathDataPointer;
Q_DECLARE_METATYPE(PathDataPointer);

typedef QWeakPointer<PathData> PathDataWeakPointer;
Q_DECLARE_METATYPE(PathDataWeakPointer);

#endif // PATHDATA_H
