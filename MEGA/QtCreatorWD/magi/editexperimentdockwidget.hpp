#ifndef EDITEXPERIMENTDOCKWIDGET_HPP
#define EDITEXPERIMENTDOCKWIDGET_HPP

#include <QDockWidget>

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
};

#endif // EDITEXPERIMENTDOCKWIDGET_HPP
