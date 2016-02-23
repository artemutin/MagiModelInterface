#ifndef OUTPUTRESULTFORM_HPP
#define OUTPUTRESULTFORM_HPP

#include <QWidget>
#include <QObject>

namespace Ui {
class OutputResultForm;
}

class OutputResultForm :  public QWidget
{
    Q_OBJECT

public:
    explicit OutputResultForm(QWidget *parent = 0);
    ~OutputResultForm();

private:
    Ui::OutputResultForm *ui;
};
#endif // OUTPUTRESULTFORM_HPP
