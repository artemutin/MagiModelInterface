#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "outputresultform.hpp"
#include "editexperimentdockwidget.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->experiments = new ExperimentModel(this);
    ui->experimentsTableView->setModel(this->experiments);

    //auto experimentsWidget = new experiments_results(nullptr, this);
    //ui->centralWidget->layout()->addWidget(experimentsWidget);
    //addDockWidget(Qt::LeftDockWidgetArea, experimentsWidget);
    //connect(ui->a,  &MainWindow::initialValuesEntered, experimentsWidget, &experiments_results::startExperiment);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addButtonClicked()
{
    auto editWidget = new editExperimentDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, editWidget);
    connect(editWidget, &editExperimentDockWidget::initialValuesEntered, experiments, &ExperimentModel::addExperiment);
}

void MainWindow::startButtonClicked()
{
    //TODO: handle multiple selection
    QItemSelectionModel *select = ui->experimentsTableView->selectionModel();
    if (select->hasSelection()){
        auto selectionList = select->selectedRows();
        //start selected experiment
        experiments->startExperiment( selectionList.first() );
    }

}

void MainWindow::showButtonClicked()
{
    //TODO: handle multiple selection
    QItemSelectionModel *select = ui->experimentsTableView->selectionModel();
    if (select->hasSelection()){
        auto selectionList = select->selectedRows();
        int row = selectionList.first().row();

        //если имеются результат (валидный шаред пойнтер)
        if (auto result = experiments->getResult( row) ){
            auto resultForm = new OutputResultForm(this);
            //creation of result model to display in table
            auto resultModel = new ResultModel(result);
            resultForm->addResult(resultModel);
            addDockWidget(Qt::LeftDockWidgetArea, resultForm);
        }
    }
}
