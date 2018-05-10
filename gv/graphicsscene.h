#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QMap>

class QTouchEvent;
class PathGraphicsItem;

class GraphicsScene : public QGraphicsScene
{
        Q_OBJECT

    public:

        explicit GraphicsScene(QObject * parent = nullptr);

        bool    event(QEvent * event) override;

    protected:

        void    mousePressEvent(QGraphicsSceneMouseEvent * event) override;
        void    mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
        void    mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;
};

#endif // SCENE_H
