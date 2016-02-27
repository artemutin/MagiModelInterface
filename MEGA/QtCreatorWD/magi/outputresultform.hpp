#ifndef OUTPUTRESULTFORM_HPP
#define OUTPUTRESULTFORM_HPP

#include <QDockWidget>
#include <QObject>
#include <QListView>
#include "resultmodel.hpp"

namespace Ui {
class OutputResultForm;
}

class OutputResultForm :  public QDockWidget
{
    Q_OBJECT

public:
    explicit OutputResultForm(QWidget *parent = 0);
    ~OutputResultForm();
public slots:
    void addResult(ResultModel* );

private:
    Ui::OutputResultForm *ui;
};
#endif // OUTPUTRESULTFORM_HPP
