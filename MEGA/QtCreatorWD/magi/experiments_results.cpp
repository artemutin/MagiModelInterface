#include "experiments_results.hpp"
#include "ui_experiments_results.h"

experiments_results::experiments_results(std::shared_ptr<ExperimentModel> experiments, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::experiments_results),
    experiments(experiments)
{
    ui->setupUi(this);
    ui->experimentsTableView->setModel(experiments.get());
}

experiments_results::~experiments_results()
{
    delete ui;
}
