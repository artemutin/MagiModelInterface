#include<QFileDialog>
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
    QItemSelectionModel *select = ui->experimentsTableView->selectionModel();
    auto selectionList = select->selectedRows();
    std::for_each(selectionList.begin(), selectionList.end(), [this](QModelIndex modelIndex){
        //start selected experiment
        experiments->startExperiment( modelIndex );
    });
}

void MainWindow::showButtonClicked()
{
    QItemSelectionModel *select = ui->experimentsTableView->selectionModel();
    auto selectionList = select->selectedRows();
    std::for_each(selectionList.begin(), selectionList.end(), [this](QModelIndex modelIndex){
        int row = modelIndex.row();
        if (auto result = experiments->getResult( row) ){
            auto resultForm = new OutputResultForm(this);
            //creation of result model to display in table
            auto resultModel = new ResultModel(result);
            resultForm->addResult(resultModel);
            addDockWidget(Qt::LeftDockWidgetArea, resultForm);
        }
    });

}

void MainWindow::deleteButtonClicked()
{
    QItemSelectionModel *select = ui->experimentsTableView->selectionModel();
    QList<QModelIndex> selectionList = select->selectedRows();
    //sort in reverse order for indeces to be correct in multiple deletion operation
    std::sort(selectionList.begin(), selectionList.end(), [](QModelIndex left, QModelIndex right){
        return left.row() > right.row();
    });
    std::for_each(selectionList.begin(), selectionList.end(), [this](QModelIndex modelIndex){
        experiments->deleteExperiment(modelIndex);
    });
}

void MainWindow::saveActionClicked()
{
    QItemSelectionModel *select = ui->experimentsTableView->selectionModel();
    auto selectionList = select->selectedRows();
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить результаты", "", "Save files (*.sav);;All files (*)");
    if (fileName.length() != 0){
        QFile* f = new QFile(fileName);
        f->open(QIODevice::WriteOnly);
        QDataStream stream(f);
        experiments->serializeAll(stream);
        f->close();
    }
}

void MainWindow::loadActionClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл с результатами", "", "Save files (*.sav);;All files (*)");
    if (fileName.length() != 0){
        QFile* f = new QFile(fileName);
        f->open(QIODevice::ReadOnly);
        QDataStream stream(f);
        experiments->deserialize(stream);
        f->close();
    }
}
