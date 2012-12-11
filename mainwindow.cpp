#include "mainwindow.hpp"

#include <QPoint>

#include <algorithm>

MainWindow::MainWindow(ThinLens::AbstractObject& object, QWidget *parent)
    : QMainWindow(parent), _object(object), _system(_object)
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
        _moveObject(event -> pos());
}

MainWindow::~MainWindow()
{
    
}
