#include "editexperimentdockwidget.hpp"
#include "ui_editexperimentdockwidget.h"

editExperimentDockWidget::editExperimentDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::editExperimentDockWidget)
{
    ui->setupUi(this);
}

editExperimentDockWidget::~editExperimentDockWidget()
{
    delete ui;
}

void editExperimentDockWidget::buttonClicked()
{
        auto simulationConstants = std::make_shared<SimulationConstants>(ui->stepUSpinBox->value(), ui->nEpochsSpinBox->value());
        auto capitalFunction  = std::make_shared<CapitalFunction>(ui->deltaSpinBox->value(), ui->savingSpinBox->value());
        auto productionFunction  = std::make_shared<ProductionFunction>(ui->regASpinBox->value(), ui->regP1SpinBox->value(),
                                                                        ui->regP2SpinBox->value(), ui->exportSpinBox->value(), ui->woodProductionSpinBox->value());
        auto costFunction  = std::make_shared<CostFunction>(ui->CostSpinBox->value(), ui->savingSpinBox->value());

        auto initialConditions = std::make_shared<FST>(ui->ProductionSpinBox->value(), ui->capitalSpinBox->value(),
                             Proportion::makeNewProportionFromAX(ui->aSpinBox->value(), ui->xSpinBox->value()), 0, 0,
                  simulationConstants, capitalFunction, productionFunction, costFunction);
        emit initialValuesEntered(initialConditions);
}
