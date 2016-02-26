#include "mainwindow.hpp"
#include <QApplication>
#include "common_constants.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    using namespace Consts;

    MainWindow w;

    w.show();

    return a.exec();
}
