#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QMap>

class QGraphicsSceneMouseEvent;
class QTouchEvent;
class QMouseEvent;

class InputHandler
{
    public:

        static InputHandler * handler();

        bool    touchEvent(QTouchEvent * event);

        void    mousePressEvent(QGraphicsSceneMouseEvent * event);
        void    mouseMoveEvent(QGraphicsSceneMouseEvent * event);
        void    mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

        void    mousePressEvent(QMouseEvent * event);
        void    mouseMoveEvent(QMouseEvent * event);
        void    mouseReleaseEvent(QMouseEvent * event);

    private:

        void    processTouchEvent(QTouchEvent * event);

        static QTouchEvent * convertEvent(QGraphicsSceneMouseEvent * event);
        static QTouchEvent * convertEvent(QMouseEvent * event);

        InputHandler() = default;

        QMap<int, int> m_map;
};

#endif // INPUTHANDLER_H
