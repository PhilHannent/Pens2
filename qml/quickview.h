#ifndef QUICKVIEW_H
#define QUICKVIEW_H

#include <QQuickWidget>

class QuickView : public QQuickWidget
{
        Q_OBJECT

    public:

        QuickView(QWidget * parent = nullptr);

    protected:

        bool    event(QEvent * event) override;

        void    mousePressEvent(QMouseEvent * event) override;
        void    mouseMoveEvent(QMouseEvent * event) override;
        void    mouseReleaseEvent(QMouseEvent * event) override;
};

#endif // QUICKVIEW_H
