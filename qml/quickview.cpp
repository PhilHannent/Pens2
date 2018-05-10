#include "quickview.h"

#include <QQmlContext>
#include <QQmlEngine>

#include "pathmodel.h"

#include "pathquickitem.h"

#include "inputhandler.h"

QuickView::QuickView(QWidget * parent)
    : QQuickWidget(parent)
{
    this->setAttribute(Qt::WA_AcceptTouchEvents);
    this->setResizeMode(ResizeMode::SizeRootObjectToView);

    qmlRegisterType<PathQuickItem>("Pens", 1, 0, "PathQuickItem");
    this->rootContext()->setContextProperty("_model", QVariant::fromValue(PathModel::model()));

    this->setSource(QUrl("qrc:/qml/QMLView.qml"));
}

bool QuickView::event(QEvent * event)
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
            return QQuickWidget::event(event);
        }
    }

    return true;
}

void QuickView::mousePressEvent(QMouseEvent * event)
{
    InputHandler::handler()->mousePressEvent(event);
}

void QuickView::mouseMoveEvent(QMouseEvent * event)
{
    InputHandler::handler()->mouseMoveEvent(event);
}

void QuickView::mouseReleaseEvent(QMouseEvent * event)
{
    InputHandler::handler()->mouseReleaseEvent(event);
}
