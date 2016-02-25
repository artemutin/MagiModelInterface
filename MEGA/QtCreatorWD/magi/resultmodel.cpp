#include "resultmodel.hpp"

ResultModel::ResultModel(ResultPtr tiers):tiers(tiers)
{

}


QModelIndex ResultModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row > (int) tiers->size() - 1 || column > NCOLS - 1){
        return QModelIndex();
    }else{
        auto it = tiers->begin();
        for (int j=0; j<row; j++, it++);
        //Very suspicious conversion, bgg
        return createIndex(row, column, static_cast<void *> (it.operator ->()) );
    }
}

QModelIndex ResultModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
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

    auto model = static_cast<SimulationTier *> (index.internalPointer());

    switch(index.column()){
        case Columns::production: return QVariant(model->production);
        case Columns::capital: return QVariant(model->capital);
        case Columns::a: return QVariant(model->proportion.a);
        case Columns::b: return QVariant(model->proportion.b);
        case Columns::x: return QVariant(model->proportion.x);
        case Columns::result: return QVariant(model->result);
        case Columns::tier: return QVariant(model->tier);
        case Columns::alpha: return QVariant(model->alpha);
        case Columns::controlParameter: return QVariant(model->controlParameter);
        default: return QVariant();
    }
}


QVariant ResultModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch(section){
            case Columns::production: return QVariant("ВВП отрасли");
            case Columns::capital: return QVariant("Капитал");
            case Columns::a: return QVariant("а");
            case Columns::b: return QVariant("b");
            case Columns::x: return QVariant("x");
            case Columns::result: return QVariant("Целевая ф-ция");
            case Columns::tier: return QVariant("Этап");
            case Columns::alpha: return QVariant("\u03B1");
            case Columns::controlParameter: return QVariant("u");
            default: return QVariant();
        }
    }

    return QVariant();
}
