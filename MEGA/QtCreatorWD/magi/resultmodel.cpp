#include "resultmodel.hpp"

ResultModel::ResultModel()
{

}


QModelIndex ResultModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row > (int) tiers->size() - 1 || column > NCOLS - 1){
        return QModelIndex();
    }else{
        auto it = tiers->begin();
        for (int j=0; j<row; j++, it++);
        return createIndex(row, column, static_cast<void *> (it.operator ->()) );
    }
}

QModelIndex ResultModel::parent(const QModelIndex &child) const
{
}

int ResultModel::rowCount(const QModelIndex &parent) const
{
    return tiers->size();
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
    return NCOLS;
}

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

    if (role != Qt::DisplayRole)
            return QVariant();


}
