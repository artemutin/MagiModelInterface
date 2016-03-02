#include "experiments_results.hpp"
#include "ui_experiments_results.h"
#include "outputresultform.hpp"
#include "mainwindow.hpp"

experiments_results::experiments_results(ExperimentModel* experiments = nullptr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::experiments_results),
    experiments(experiments)
{
    ui->setupUi(this);
    if (!this->experiments){
        this->experiments = new ExperimentModel(this);
    }

    ui->experimentsTableView->setModel(this->experiments);
    //connect(this, &experiments_results::initialValues, this->experiments, &ExperimentModel::startExperiment);
    //connect(ui->experimentsTableView, &QTableView::doubleClicked, this, &experiments_results::rowDoubleClicked);
    }

experiments_results::~experiments_results()
{
    delete ui;
}

void experiments_results::startExperiment(std::shared_ptr<ST> initialConditions)
{
    emit initialValues(initialConditions);
}

void experiments_results::rowDoubleClicked(const QModelIndex& index)
{
    auto outputForm = new OutputResultForm(this);
    auto resultModel = new ResultModel( experiments->getResult(index.row()) );
    outputForm->addResult( resultModel  );
    static_cast<MainWindow*>(this->parent())->addDockWidget(Qt::LeftDockWidgetArea, outputForm);
}
