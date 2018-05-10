#include "testdataprovider.h"

PathDataPointer TestDataProvider::getTestData()
{
    PathData * data = new PathData();

    PathDataPoint::Type type = PathDataPoint::Move;

    qreal pressue = 0.0;

    const int pointCount = 70;
    const qreal pressureChange = 1.0 / qreal(pointCount);

    for (quint32 i = 0; i < pointCount; i++)
    {
        PathDataPoint point;

        point.x = i * 10;
        point.y = (std::sin(i) * 100) + 300;

        point.pressure = pressue;
        point.rotation = 1.0;
        point.timestamp = i;
        point.area = QSizeF(0, 0);
        point.velocity = QVector2D(0, 0);
        point.type = type;

        data->addPoint(point);

        type = PathDataPoint::Line;
        pressue += pressureChange;
    }

    return PathDataPointer(data);
}

PathDataPointer TestDataProvider::getTestData2()
{
    PathData * data = new PathData();

    auto addPoint = [ = ](qreal x, qreal y, PathDataPoint::Type type)
    {
        PathDataPoint point;

        point.x = x;
        point.y = y;

        point.pressure = 1.0;
        point.rotation = 1.0;
        point.timestamp = 0;
        point.area = QSizeF(0, 0);
        point.velocity = QVector2D(0, 0);
        point.type = type;

        data->addPoint(point);
    };

    addPoint(0, 0, PathDataPoint::Move);
    addPoint(200, 200, PathDataPoint::Curve);
    addPoint(400, 600, PathDataPoint::CurveData);
    addPoint(700, 400, PathDataPoint::CurveData);

    return PathDataPointer(data);
}
