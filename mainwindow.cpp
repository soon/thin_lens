#include "mainwindow.hpp"

#include <QtCore/QPoint>

#include <algorithm>

MainWindow::MainWindow
(
    ThinLens::AbstractObject &object,
    int focus,
    unsigned flags,
    QWidget *parent
) : QMainWindow(parent), _object(object), _system(_object, focus, flags)
{
    setCentralWidget(&_system);
}

void MainWindow::_moveObject(const QPoint &center)
{
    auto delta = center - QPoint
    (
        (_object.getBegin().x() + _object.getEnd().x()) / 2,
        (_object.getBegin().y() + _object.getEnd().y()) / 2
    );

    _object.setBegin(_object.getBegin() + delta);
    _object.setEnd(_object.getEnd() + delta);
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event -> button() == Qt::LeftButton)
        _moveObject(event -> pos());
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event -> buttons() & Qt::LeftButton)
    {
        auto p = event -> pos();
        if((p.x() > 0) && (p.x() < width()) && (p.y() > 0) && (p.y() < height()))
            _moveObject(p);
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    _system.setFocus
    (
        _system.getFocus() +
        (
            (event -> delta() > 0)  ?
            (DELTA_FOCUS)           :
            (-DELTA_FOCUS)
        )
    );
    update();
}

MainWindow::~MainWindow()
{
    
}
