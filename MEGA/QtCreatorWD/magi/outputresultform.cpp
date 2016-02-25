#include "outputresultform.hpp"
#include "ui_outputresultform.h"

OutputResultForm::OutputResultForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputResultForm)
{
    ui->setupUi(this);
}

OutputResultForm::~OutputResultForm()
{
    delete ui;
}

void OutputResultForm::addResult(ResultModel * model)
{
    ui->resultsTableView->setModel(model);
}
