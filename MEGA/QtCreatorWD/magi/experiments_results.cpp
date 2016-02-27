#include "experiments_results.hpp"
#include "ui_experiments_results.h"

experiments_results::experiments_results(ExperimentModel* experiments = nullptr, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::experiments_results),
    experiments(experiments)
{
    ui->setupUi(this);
    if (!experiments){
        experiments = new ExperimentModel(this);
    }

    ui->experimentsTableView->setModel(experiments);
    connect(this, &experiments_results::initialValues, experiments, &ExperimentModel::startExperiment);
    }

experiments_results::~experiments_results()
{
    delete ui;
}

void experiments_results::startExperiment(std::shared_ptr<FST> initialConditions)
{
   emit initialValues(initialConditions);
}
