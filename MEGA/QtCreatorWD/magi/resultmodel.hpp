#ifndef RESULTMODEL_HPP
#define RESULTMODEL_HPP

#include <QAbstractItemModel>
#include "model.hpp"

class ResultModel : public QAbstractItemModel
{
    Q_OBJECT

    ResultPtr tiers;
    static const int NCOLS = 9;

public:
    ResultModel(ResultPtr tiers);

    // QAbstractItemModel interface
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    enum Columns {
        tier,
        controlParameter,
        x,
        result,
        production,
        capital,
        a,
        b,
        alpha
    };

};


#endif // RESULTMODEL_HPP
