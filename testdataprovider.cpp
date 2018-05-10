#include "testdataprovider.h"

PathDataPointer TestDataProvider::getTestData()
{
    PathData * data = new PathData();

    PathDataPoint::Type type = PathDataPoint::Move;

    qreal pressue = 0.0;

    const int pointCount = 70;
    const qreal pressureChange = 1.0 / qreal(pointCount);

    for (int i = 0; i < pointCount; i++)
    {
        PathDataPoint point;

        point.x = i * 10;
        point.y = std::sin(i) * 100;

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
