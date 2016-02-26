#include "experiments_results.hpp"
#include "ui_experiments_results.h"

experiments_results::experiments_results(QWidget *parent, std::shared_ptr<ExperimentModel> experiments) :
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
