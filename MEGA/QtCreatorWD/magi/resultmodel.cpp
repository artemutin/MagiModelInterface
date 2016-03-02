#include "resultmodel.hpp"
#include "common_constants.hpp"

constexpr Consts::Columns ResultModel::columns[];

std::map<int, Consts::Columns> ResultModel::columnByInt = [](){
    int i = -1;
    std::map<int, Consts::Columns> ret;
    for (auto en : ResultModel::columns){
        ret.insert({++i, en});
    }
    return ret;
}();

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
{using namespace Consts;
    if (!index.isValid())
            return QVariant();

    if (role != Qt::DisplayRole)
            return QVariant();

    auto model = static_cast<ST *> (index.internalPointer());
    auto colEnum = columnByInt.find(index.column())->second;

    switch(colEnum){
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
{using namespace Consts;
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        auto colEnum = columnByInt.find(section)->second;
        QString label = Labels.find(colEnum)->second;

        return QVariant(label);
    }

    return QVariant();
}
