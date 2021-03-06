#include "outputresultform.hpp"

OutputResultForm::OutputResultForm(QWidget *parent) :
    QDockWidget(parent), resultsTableView(new QTableView)
{
    this->setAllowedAreas(Qt::LeftDockWidgetArea);
    this->setWidget(resultsTableView);
    this->setWindowTitle("Подробный результат");
}

OutputResultForm::~OutputResultForm()
{
    delete resultsTableView;
}

void OutputResultForm::addResult(ResultModel * model)
{
    resultsTableView->setModel(model);
}
