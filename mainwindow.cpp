#include "mainwindow.h"

#include "pathdata.h"
#include "testdataprovider.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>

#include "gv/graphicsview.h"
#include "gv/graphicsscene.h"
#include "gv/pathgraphicsitem.h"

#include "qml/quickview.h"

#include "pathmodel.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    QGraphicsScene * scene = new GraphicsScene(this);
    QGraphicsView * gvView = new GraphicsView(scene);

    ////////////////////////////////////////////////////////////////////////////

    QuickView * quickView = new QuickView();

    ////////////////////////////////////////////////////////////////////////////

    QWidget * widget = new QWidget();
    QVBoxLayout * outerLayout = new QVBoxLayout(widget);

    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);

    QGridLayout * viewsLayout = new QGridLayout();
    viewsLayout->setContentsMargins(0, 0, 0, 0);
    viewsLayout->setSpacing(0);

    ////////////////////////////////////////////////////////////////////////////

    viewsLayout->addWidget(gvView, 0, 0);
    viewsLayout->addWidget(quickView, 0, 1);

    viewsLayout->setColumnStretch(0, 1);
    viewsLayout->setColumnStretch(1, 1);

    ////////////////////////////////////////////////////////////////////////////

    outerLayout->addLayout(viewsLayout);

    QSlider * slider = new QSlider();
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(50, 250);
    slider->setValue(100);

    connect(slider, &QSlider::valueChanged, this, [ = ](int value)
    {
        const qreal scale = qreal(value) * 0.01;

        QTransform t;
        t.scale(scale, scale);
        gvView->setTransform(t);
    });

    outerLayout->addWidget(slider);

    ////////////////////////////////////////////////////////////////////////////

    QHBoxLayout * controlsLayout = new QHBoxLayout();

    QPushButton * clear = new QPushButton("Clear");
    controlsLayout->addWidget(clear);

    QPushButton * load = new QPushButton("Load");
    controlsLayout->addWidget(load);

    QPushButton * save = new QPushButton("Save");
    controlsLayout->addWidget(save);

    connect(clear, &QPushButton::clicked, this, [ = ]()
    {
        PathModel::model()->clear();
    });

    connect(load, &QPushButton::clicked, this, [ = ]()
    {
        PathModel::model()->load();
    });

    connect(save, &QPushButton::clicked, this, [ = ]()
    {
        PathModel::model()->save();
    });

    outerLayout->addLayout(controlsLayout);

    this->setCentralWidget(widget);

    ////////////////////////////////////////////////////////////////////////////

    //PathGraphicsItem * pgi = new PathGraphicsItem();
    //pgi->setPathData(TestDataProvider::getTestData());
    //
    //scene->addItem(pgi);
}
