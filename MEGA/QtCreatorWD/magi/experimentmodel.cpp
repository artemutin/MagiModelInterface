#include "experimentmodel.hpp"

ExperimentModel::ExperimentModel()
{

}


QModelIndex ExperimentModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row > experiments.size()-1 || column > NCOLS -1){
        return QModelIndex();
    }else{
        //HOLY COW, IT IS UGLY AS HELL, TODO SMTH WITH IT!!!
        return createIndex(row, column,
                           (void*) NULL );
    }
}

QModelIndex ExperimentModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int ExperimentModel::rowCount(const QModelIndex &parent) const
{
    return experiments.size();
}

int ExperimentModel::columnCount(const QModelIndex &parent) const
{
    return NCOLS;
}

QVariant ExperimentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

    if (role != Qt::DisplayRole)
            return QVariant();

    auto params = static_cast<const ExperimentParams *> (&(experiments[index.row()]) );
    auto model = params->initialConditions;

    switch(index.column()){
        case Columns::production: return QVariant(model->production);
        case Columns::capital: return QVariant(model->capital);
        case Columns::a: return QVariant(model->proportion.a);
        case Columns::b: return QVariant(model->proportion.b);
        case Columns::x: return QVariant(model->proportion.x);
        case Columns::result: return QVariant(model->result);
        case Columns::nTiers: return QVariant(model->simConstants->numEpochs);
        case Columns::cost: return QVariant(model->costFunction->c);
        case Columns::delta: return  QVariant(model->capitalFunction->savings);
        case Columns::exportCost: return  QVariant(model->productionFunction->ef.e);
        case Columns::regA: return  QVariant(model->productionFunction->rf.a);
        case Columns::regP1: return  QVariant(model->productionFunction->rf.p1);
        case Columns::regP2: return  QVariant(model->productionFunction->rf.p2);
        case Columns::savings: return  QVariant(model->capitalFunction->savings);
        case Columns::woodProduction: return  QVariant(model->productionFunction->woodProduction);
        case Columns::status: return QVariant(
                    [params]() {
                    switch(params->status){
                                case notStarted: return "not started";
                                case inProgress: return "in progress";
                                 case done: return "done";
                                }
                    }()
        );
        default: return QVariant();
    }
}


QVariant ExperimentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {

    }

    return QVariant();
}
