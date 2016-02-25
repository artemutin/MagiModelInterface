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

QListView *OutputResultForm::getListView()
{
    return ui->listView;
}

void OutputResultForm::addResult(ResultModel * model)
{
    ui->listView->setModel(model);
}
