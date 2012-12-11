// #include "mainwindow.hpp"

#include <QApplication>
// #include <QtGui/QMainWindow>
#include <QPoint>

#include "arrow.hpp"
#include "mainwindow.hpp"
#include "thin_lens_widget/thinlenssystem.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Arrow arrow(QPoint(20, 60), QPoint(20, 100));
    MainWindow w(arrow);

    w.show();
    
    return a.exec();
}
