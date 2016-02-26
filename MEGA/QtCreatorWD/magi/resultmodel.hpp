#ifndef RESULTMODEL_HPP
#define RESULTMODEL_HPP

#include <QAbstractItemModel>
#include "model.hpp"
#include "common_constants.hpp"

//this class represents full chain of parameters-tiers simulation values
class ResultModel : public QAbstractItemModel
{
    Q_OBJECT

    ResultPtr tiers;
    static const int NCOLS = 9;

    static constexpr Consts::Columns columns[] = {
        Consts::production,
        Consts::capital,
        Consts::a,
        Consts::b,
        Consts::x,
        Consts::result,
        Consts::tier,
        Consts::alpha,
        Consts::controlParameter
    };

    static std::map<int, Consts::Columns> columnByInt;
public:
    ResultModel(ResultPtr tiers);

    // QAbstractItemModel interface
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const; 

};


#endif // RESULTMODEL_HPP
