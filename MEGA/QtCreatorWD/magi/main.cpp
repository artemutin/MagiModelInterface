#include "mainwindow.hpp"
#include <QApplication>
#include "model.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    auto simulationConstants = std::make_shared<SimulationConstants>(0.1, 0);
    auto capitalFunction  = std::make_shared<CapitalFunction>(0.95, 0.2);
    auto productionFunction  = std::make_shared<ProductionFunction>(100, 0.7, 0.3, 80, 1e5);
    auto costFunction  = std::make_shared<CostFunction>(1000, 0.2);

    w.show();

    return a.exec();
}
