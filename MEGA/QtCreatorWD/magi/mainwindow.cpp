#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClicked()
{
    auto simulationConstants = std::make_shared<SimulationConstants>(ui->stepUSpinBox->value(), ui->nEpochsSpinBox->value());
    auto capitalFunction  = std::make_shared<CapitalFunction>(ui->deltaSpinBox->value(), ui->savingSpinBox->value());
    auto productionFunction  = std::make_shared<ProductionFunction>(ui->regASpinBox->value(), ui->regP1SpinBox->value(),
                                                                    ui->regP2SpinBox->value(), ui->exportSpinBox->value(), ui->woodProductionSpinBox->value());
    auto costFunction  = std::make_shared<CostFunction>(ui->CostSpinBox->value(), ui->savingSpinBox->value());

    FST* start = new FST(ui->ProductionSpinBox->value(), ui->capitalSpinBox->value(),
                         Proportion::makeNewProportionFromAX(ui->aSpinBox->value(), ui->bSpinBox->value()), 0, 0,
              simulationConstants, capitalFunction, productionFunction, costFunction);
    result = start->diveInto();
 }
