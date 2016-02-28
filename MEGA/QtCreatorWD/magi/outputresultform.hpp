#ifndef OUTPUTRESULTFORM_HPP
#define OUTPUTRESULTFORM_HPP

#include <QDockWidget>
#include <QObject>
#include <QTableView>
#include "resultmodel.hpp"


class OutputResultForm :  public QDockWidget
{
    Q_OBJECT

    QTableView* resultsTableView;
public:
    explicit OutputResultForm(QWidget *parent = 0);
    void addResult(ResultModel* );
    ~OutputResultForm();
public slots:

};
#endif // OUTPUTRESULTFORM_HPP
