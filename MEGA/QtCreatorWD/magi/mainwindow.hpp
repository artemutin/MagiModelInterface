#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "model.hpp"
#include "outputresultform.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<OutputResultForm> outputForm;
    ResultPtr result;
private slots:
    void buttonClicked();
signals:
    void initialValuesEntered(std::shared_ptr<FST> initialConditions);
};

#endif // MAINWINDOW_HPP
