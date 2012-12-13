#include <QtGui/QApplication>
#include <QtCore/QPoint>

#include "arrow.hpp"
#include "mainwindow.hpp"
#include "thin_lens_widget/thinlenssystem.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Arrow arrow(QPoint(200, 100), QPoint(200, 50));
    MainWindow w(arrow);

    w.showMaximized();
    
    return a.exec();
}
