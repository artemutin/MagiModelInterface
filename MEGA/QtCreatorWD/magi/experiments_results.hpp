#ifndef EXPERIMENTS_RESULTS_HPP
#define EXPERIMENTS_RESULTS_HPP

#include <QDockWidget>
#include <memory>
#include "experimentmodel.hpp"

namespace Ui {
class experiments_results;
}

class experiments_results : public QDockWidget
{
    Q_OBJECT

public:
    explicit experiments_results(ExperimentModel *experiments, QWidget *parent = 0);
    ~experiments_results();

private:
    Ui::experiments_results *ui;
    ExperimentModel* experiments;
public slots:
    void startExperiment(std::shared_ptr<FST> initialConditions);
signals:
    void initialValues(std::shared_ptr<FST> initialConditions);
    //it should handled doubleClick on row
    //to open appropriate results
private slots:
    void rowDoubleClicked(const QModelIndex & );
    //and finaly, it all must be converted to DockedWidgets
    //like OpenCS did
    //after that, I have two options -
    //1 - parallell calculations fix and benchmarking
    //2 - some export capabilities - JSON, CSV?
    //and also saving couples with above
};

#endif // EXPERIMENTS_RESULTS_HPP
