#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
        Q_OBJECT

    public:

        explicit GraphicsView(QWidget * parent = nullptr);
        GraphicsView(QGraphicsScene * scene, QWidget * parent = nullptr);

    protected:

        void    resizeEvent(QResizeEvent * event) override;

    private:

        void    init();
};

#endif // VIEW_H
