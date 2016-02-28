#include "outputresultform.hpp"

OutputResultForm::OutputResultForm(QWidget *parent) :
    QDockWidget(parent), resultsTableView(new QTableView)
{
    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    this->setWidget(resultsTableView);
}

OutputResultForm::~OutputResultForm()
{
    delete resultsTableView;
}

void OutputResultForm::addResult(ResultModel * model)
{
    resultsTableView->setModel(model);
}
