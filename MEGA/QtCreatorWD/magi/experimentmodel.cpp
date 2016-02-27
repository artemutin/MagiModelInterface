#include "experimentmodel.hpp"
#include "ui_outputresultform.h"

constexpr Consts::Columns ExperimentModel::columns[];

std::map<int, Consts::Columns> ExperimentModel::columnByInt = [](){
    int i = -1;
    std::map<int, Consts::Columns> ret;
    for (auto en : ExperimentModel::columns){
        ret.insert({++i, en});
    }
    return ret;
}();

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

    auto params = experiments[index.row()];
    auto model = params->initialConditions;

    using namespace Consts;
    auto colEnum = columnByInt.find(index.column());
    switch(colEnum->second){
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
                                default: return "not started";
                                }
                    }()
        );
        default: return QVariant();
    }
}


QVariant ExperimentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    using namespace   Consts;
    if (role != Qt::DisplayRole)
        return QVariant();


    if (orientation == Qt::Horizontal) {
        auto colEnum = columnByInt.find(section)->second;
        QString label = Labels.find(colEnum)->second;

        return QVariant(label);
    }

    return QVariant();
}

void ExperimentModel::startExperiment(std::shared_ptr<FST> initialConditions)
{
    //for now, i see it, as we create new ExperimentParams
    auto newExperiment = new ExperimentParams(initialConditions, notStarted, this);
    //run FST in here, in other thread for best
    connect(this, SIGNAL(startComputation()), newExperiment, SLOT(startComputation()));
    //and insertRow it here.
    insertRow(rowCount(QModelIndex()), createIndex(0, 0, newExperiment ) );
    //it should be added and displayed in table
    //but, what about update of model?
    //seems to me, we need to connect some signals
    /*
            outputForm = std::shared_ptr<OutputResultForm> (new OutputResultForm() );
            connect(this, SIGNAL( modelEvaluated(ResultModel* ) ), outputForm.get(), SLOT(show() ) );
            connect(this, SIGNAL( modelEvaluated(ResultModel*) ), outputForm.get(), SLOT(addResult(ResultModel*) ) );
            auto model = std::make_shared<ResultModel>(result);
            emit modelEvaluated(model);
     */
}


bool ExperimentModel::insertRows(int row, int count, const QModelIndex &parent)
{
    //implement inserting of experiment results
    if (row < 0 || row > rowCount(QModelIndex())){
        return false;
    }
    auto insertIter = experiments.begin() += row;
    auto itemPointer = static_cast<ExperimentParams**> (parent.internalPointer());
    //TODO: Childrens handling!
    experiments.insert(insertIter, itemPointer, itemPointer);
    return true;
}

ExperimentParams::ExperimentParams(std::shared_ptr<FST> initialConditions, ExperimentStatus status, QObject *parent):
    initialConditions(initialConditions), status(status), QObject(parent)
{
}

void ExperimentParams::startComputation()
{
    result = initialConditions->diveInto();
    emit computationFinished();
}
