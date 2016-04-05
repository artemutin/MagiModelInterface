#include "editexperimentdockwidget.hpp"
#include "ui_editexperimentdockwidget.h"

editExperimentDockWidget::editExperimentDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::editExperimentDockWidget)
{
    ui->setupUi(this);
    emit ui->aSpinBox->valueChanged(0.1);
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
                                                                        ui->regP2SpinBox->value(), ui->exportSpinBox->value(), ui->woodProductionSpinBox->value()*1000);
        auto costFunction  = std::make_shared<CostFunction>(ui->CostSpinBox->value()*1000, ui->savingSpinBox->value());

        auto initialConditions = std::make_shared<ST>(ui->ProductionSpinBox->value()*1000, ui->capitalSpinBox->value()*1000,
                             Proportion::makeNewProportionFromAX(ui->aSpinBox->value(), ui->xSpinBox->value()), 0, 0,
                  simulationConstants, capitalFunction, productionFunction, costFunction);
        emit initialValuesEntered(initialConditions);
}

void editExperimentDockWidget::abxHaveChanged()
{
    double b = Proportion::calcB(ui->aSpinBox->value(), ui->xSpinBox->value());
    ui->bSpinBox->setValue(b);
    if (b < 0 || b > 1){
        ui->addButton->setEnabled(false);
    }else{
        ui->addButton->setEnabled(true);
    }
}
