#include "inputhandler.h"

#include <QTouchEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

#include "pathmodel.h"

InputHandler * InputHandler::handler()
{
    static InputHandler * handler = new InputHandler();
    return handler;
}

bool InputHandler::touchEvent(QTouchEvent * event)
{
    this->processTouchEvent(event);
    return true;
}

void InputHandler::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (event->source() == Qt::MouseEventSynthesizedBySystem)
    {
        return;
    }

    QTouchEvent * te = this->convertEvent(event);
    this->processTouchEvent(te);
    delete te;
}

void InputHandler::mousePressEvent(QMouseEvent * event)
{
    if (event->source() == Qt::MouseEventSynthesizedBySystem)
    {
        return;
    }

    QTouchEvent * te = this->convertEvent(event);
    this->processTouchEvent(te);
    delete te;
}

void InputHandler::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    this->mousePressEvent(event);
}

void InputHandler::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    this->mousePressEvent(event);
}

void InputHandler::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::NoButton)
    {
        return;
    }

    this->mousePressEvent(event);
}

void InputHandler::mouseReleaseEvent(QMouseEvent * event)
{
    this->mousePressEvent(event);
}

void InputHandler::processTouchEvent(QTouchEvent * event)
{
    for (const QTouchEvent::TouchPoint & tp : event->touchPoints())
    {
        if (tp.state() == Qt::TouchPointStationary)
        {
            continue;
        }

        PathModel * m = PathModel::model();

        if (tp.state() == Qt::TouchPointPressed)
        {
            m_map.insert(tp.id(), m->addPathData());
        }

        PathDataPoint p;
        p.x = tp.pos().x();
        p.y = tp.pos().y();

        p.pressure = tp.pressure();
        p.rotation = tp.rotation();
        p.timestamp = 0;
        p.area = tp.ellipseDiameters();
        p.velocity = tp.velocity();
        p.type = tp.state() == Qt::TouchPointPressed ? PathDataPoint::Move : PathDataPoint::Line;

        m->pathData(m_map.value(tp.id()))->addPoint(p);

        if (tp.state() == Qt::TouchPointReleased)
        {
            m_map.remove(tp.id());
        }
    }
}

QTouchEvent * InputHandler::convertEvent(QGraphicsSceneMouseEvent * event)
{
    QList<QTouchEvent::TouchPoint> p;

    p.append(QTouchEvent::TouchPoint());
    QTouchEvent::TouchPoint & t = p.back();

    // lets not use 0, which will likely be a touch, stops mouse and
    // touch ids getting mixed in fringe use cases
    t.setId(-210787);

    t.setPos(event->scenePos());
    t.setScenePos(event->scenePos());
    t.setScreenPos(event->screenPos());

    t.setLastPos(event->lastPos());
    t.setLastScenePos(event->lastScenePos());
    t.setLastScreenPos(event->lastScreenPos());

    t.setStartPos(event->buttonDownPos(event->button()));
    t.setStartScenePos(event->buttonDownScenePos(event->button()));
    t.setStartScreenPos(event->buttonDownScreenPos(event->button()));

    QEvent::Type teType = QEvent::TouchBegin;
    Qt::TouchPointStates teStates = Qt::TouchPointPressed;

    switch (event->type())
    {
        case QEvent::GraphicsSceneMousePress:
        {
            t.setState(Qt::TouchPointPressed);
            break;
        }

        case QEvent::GraphicsSceneMouseMove:
        {
            teType = QEvent::TouchUpdate;
            teStates = Qt::TouchPointMoved;
            t.setState(Qt::TouchPointMoved);
            break;
        }

        case QEvent::GraphicsSceneMouseRelease:
        {
            teType = QEvent::TouchEnd;
            teStates = Qt::TouchPointReleased;
            t.setState(Qt::TouchPointReleased);
            break;
        }

        default:
        {
            break;
        }
    }

    t.setPressure(1);

    QTouchEvent * te = new QTouchEvent(teType, nullptr, event->modifiers(), teStates, p);
    return te;
}

QTouchEvent * InputHandler::convertEvent(QMouseEvent * event)
{
    QList<QTouchEvent::TouchPoint> p;

    p.append(QTouchEvent::TouchPoint());
    QTouchEvent::TouchPoint & t = p.back();

    // lets not use 0, which will likely be a touch, stops mouse and
    // touch ids getting mixed in fringe use cases
    t.setId(-210787);

    t.setPos(event->pos());
    t.setScenePos(event->pos());
    t.setScreenPos(event->screenPos());

    //t.setLastPos(event->lastPos());
    //t.setLastScenePos(event->lastScenePos());
    //t.setLastScreenPos(event->lastScreenPos());
    //
    //t.setStartPos(event->buttonDownPos(event->button()));
    //t.setStartScenePos(event->buttonDownScenePos(event->button()));
    //t.setStartScreenPos(event->buttonDownScreenPos(event->button()));

    QEvent::Type teType = QEvent::TouchBegin;
    Qt::TouchPointStates teStates = Qt::TouchPointPressed;

    switch (event->type())
    {
        case QEvent::MouseButtonPress:
        {
            t.setState(Qt::TouchPointPressed);
            break;
        }

        case QEvent::MouseMove:
        {
            teType = QEvent::TouchUpdate;
            teStates = Qt::TouchPointMoved;
            t.setState(Qt::TouchPointMoved);
            break;
        }

        case QEvent::MouseButtonRelease:
        {
            teType = QEvent::TouchEnd;
            teStates = Qt::TouchPointReleased;
            t.setState(Qt::TouchPointReleased);
            break;
        }

        default:
        {
            break;
        }
    }

    t.setPressure(1);

    QTouchEvent * te = new QTouchEvent(teType, nullptr, event->modifiers(), teStates, p);
    return te;
}
