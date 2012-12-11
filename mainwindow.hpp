#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPoint>

#include <memory>

#include "arrow.hpp"
#include "thin_lens_widget/abstractobject.hpp"
#include "thin_lens_widget/thinlenssystem.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(ThinLens::AbstractObject &, QWidget *parent = 0);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    void _moveObject(const QPoint &center);

private:
    ThinLens::AbstractObject &_object;
    ThinLens::ThinLensSystem _system;
};

#endif // MAINWINDOW_HPP
