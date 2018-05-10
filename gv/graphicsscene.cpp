#include "graphicsscene.h"

#include <QTouchEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "gv/pathgraphicsitem.h"

#include "inputhandler.h"

#include "pathmodel.h"

GraphicsScene::GraphicsScene(QObject * parent)
    : QGraphicsScene(parent)
{
    this->setSceneRect(0, 0, 1000, 1000);

    /////////////////////////

    PathModel * m = PathModel::model();

    auto initFromModel = [ = ]()
    {
        for (int i = 0; i < m->rowCount(QModelIndex()); i++)
        {
            PathGraphicsItem * item = new PathGraphicsItem();
            item->setPathData(m->pathData(i));
            this->addItem(item);
        }
    };

    connect(m, &PathModel::modelReset, this, [ = ]()
    {
        this->clear();
        initFromModel();
    });

    connect(m, &PathModel::rowsInserted, this, [ = ](const QModelIndex &, int first, int last)
    {
        for (int i = first; i <= last; i++)
        {
            PathGraphicsItem * item = new PathGraphicsItem();
            item->setPathData(m->pathData(i));
            this->addItem(item);
        }
    });
}

bool GraphicsScene::event(QEvent * event)
{
    switch (static_cast<int>(event->type()))
    {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        case QEvent::TouchCancel:
        {
            InputHandler::handler()->touchEvent(static_cast<QTouchEvent *>(event));
            break;
        }

        default:
        {
            return QGraphicsScene::event(event);
        }
    }

    return true;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    InputHandler::handler()->mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    InputHandler::handler()->mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    InputHandler::handler()->mouseReleaseEvent(event);
}

