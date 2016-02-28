#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "model.hpp"
#include "outputresultform.hpp"
#include "experiments_results.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    // !!!!!!!! OutputResultForm* addOutputForm();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<OutputResultForm*> outputForms;
    ExperimentModel* experiments;
private slots:
    void addButtonClicked();
    void startButtonClicked();
signals:
    void initialValuesEntered(std::shared_ptr<FST> initialConditions);
};

#endif // MAINWINDOW_HPP
