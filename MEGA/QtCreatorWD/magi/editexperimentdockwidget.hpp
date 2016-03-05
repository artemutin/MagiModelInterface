#ifndef EDITEXPERIMENTDOCKWIDGET_HPP
#define EDITEXPERIMENTDOCKWIDGET_HPP

#include <QDockWidget>
#include <memory>
#include "model.hpp"

namespace Ui {
class editExperimentDockWidget;
}

class editExperimentDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit editExperimentDockWidget(QWidget *parent = 0);
    ~editExperimentDockWidget();

private:
    Ui::editExperimentDockWidget *ui;

private slots:
    void buttonClicked();
    void abxHaveChanged();
signals:
    void initialValuesEntered(std::shared_ptr<ST> initialConditions);
};

#endif // EDITEXPERIMENTDOCKWIDGET_HPP
