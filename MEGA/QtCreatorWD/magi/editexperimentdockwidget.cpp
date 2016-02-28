#include "editexperimentdockwidget.hpp"
#include "ui_editexperimentdockwidget.h"

editExperimentDockWidget::editExperimentDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::editExperimentDockWidget)
{
    ui->setupUi(this);
}

editExperimentDockWidget::~editExperimentDockWidget()
{
    delete ui;
}
