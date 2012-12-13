#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui/QMainWindow>
#include <QtCore/QPoint>

#include <memory>

#include "arrow.hpp"
#include "thin_lens_widget/abstractobject.hpp"
#include "thin_lens_widget/thinlenssystem.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow
    (
        ThinLens::AbstractObject &,
        int focus = 40,
        unsigned flags = ThinLens::ThinLensSystem::showInfo,
        QWidget *parent = 0
    );
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

private:
    void _moveObject(const QPoint &center);

private:
    ThinLens::AbstractObject &_object;
    ThinLens::ThinLensSystem _system;

private:
    static constexpr auto DELTA_FOCUS = 2u;
};

#endif // MAINWINDOW_HPP
