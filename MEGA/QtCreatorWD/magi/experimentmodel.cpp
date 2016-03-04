#include "experimentmodel.hpp"
#include "serialization.hpp"
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

constexpr Consts::Columns ExperimentModel::columns[];

std::map<int, Consts::Columns> ExperimentModel::columnByInt = [](){
    int i = -1;
    std::map<int, Consts::Columns> ret;
    for (auto en : ExperimentModel::columns){
        ret.insert({++i, en});
    }
    return ret;
}();

ExperimentModel::ExperimentModel(QObject *parent):QAbstractItemModel(parent)
{
}

ResultPtr ExperimentModel::getResult(int row)
{
    return experiments[row]->getResult();
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
        case Columns::stepU: return QVariant(model->simConstants->stepU);
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
    if (orientation == Qt::Vertical){
        return QVariant(section);
    }
    return QVariant();
}

void ExperimentModel::startExperiment(const QModelIndex & index)
{
    ExperimentParams* experiment = experiments.at(index.row());
    if (experiment->getStatus() != notStarted){
        return;//experiment has already been done
    }else{
        experiment->setStatus(inProgress);
        emit dataChanged(index, index);
        //must return a link to params when finished
        connect(experiment, &ExperimentParams::computationFinished, this, &ExperimentModel::computationFinished);
        //actually start the experiment
        experiment->startComputation();
    }
}

void ExperimentModel::addExperiment(std::shared_ptr<ST> initialConditions)
{
    auto newExperiment = new ExperimentParams(initialConditions, notStarted, this);
    //and insertData it here.
    setData(createIndex(0, 0, this), QVariant::fromValue(newExperiment));
}

void ExperimentModel::deleteExperiment(const QModelIndex & index)
{
    beginRemoveRows(index, index.row(), index.row());
    auto it = experiments.begin();
    std::advance(it, index.row());
    experiments.erase(it);
    endRemoveRows();
}

void ExperimentModel::serializeAll(QDataStream &stream)
{
    QVector<ExperimentParams> params(experiments.size());
    std::transform(experiments.begin(), experiments.end(), params.begin(), [](auto ptr){
        return *ptr;
    });
    stream << params;
}

void ExperimentModel::computationFinished(ExperimentParams * experiment)
{
    //experiment has been done, and return pointer to themself
    //which we have saved at experiments vector
    auto it = std::find(experiments.begin(), experiments.end(), experiment);
    int row = std::distance(experiments.begin(), it);
    emit dataChanged(createIndex(row, 0, this), createIndex(row, NCOLS, this));
}


bool ExperimentModel::insertRows(int row, int count, const QModelIndex &parent)
{
    //implement inserting of experiment results
    if (row < 0 || row > rowCount(QModelIndex())){
        return false;
    }
    auto insertIter = experiments.begin() += row;
    if (count == 1){
        emit beginInsertRows(createIndex(row, 0, this), row, row+count);

        auto item = static_cast<ExperimentParams**> (parent.internalPointer());
        //TODO: Childrens handling!
        experiments.insert(insertIter, *item);

        emit endInsertRows();
        return true;
    }else{
        return false;
    }

}

ResultPtr ExperimentParams::getResult() const
{
    return result;
}

ExperimentStatus ExperimentParams::getStatus() const
{
    return status;
}

void ExperimentParams::setStatus(const ExperimentStatus &value)
{
    status = value;
}

QFutureWatcher<ResultPtr>& ExperimentParams::getWatcher()
{
    return watcher;
}

ExperimentParams::ExperimentParams(std::shared_ptr<ST> initialConditions, ExperimentStatus status, QObject *parent):
    initialConditions(initialConditions), status(status), QObject(parent)
{
}

ExperimentParams::ExperimentParams(const ExperimentParams &a):QObject(a.parent())
{
    initialConditions = a.initialConditions;
    result = a.result;
    status = a.status;
}

ExperimentParams::~ExperimentParams()
{
    if (initialConditions){
        initialConditions.~__shared_ptr();
    }
    if (result){
        result.~__shared_ptr();
    }
}

ExperimentParams ExperimentParams::operator =(const ExperimentParams &a)
{
    initialConditions = a.initialConditions;
    result = a.result;
    status = a.status;
    return *this;
}

bool ExperimentParams::operator ==(const ExperimentParams &p) const
{
    bool vectorComparison = true;
    if (p.result != result){
        for(auto i=p.result->begin(), j=result->begin(); i != p.result->end() && j != result->end(); i++, j++){
            if (!(*i == *j) ){
                vectorComparison = false;
                break;
            }
        }
    }

    return (*p.initialConditions) == *initialConditions && p.status == status &&
        vectorComparison;
}

void ExperimentParams::startComputation()
{
    connect(&watcher, &QFutureWatcher<ResultPtr>::finished, this, &ExperimentParams::futureFinished);
    auto future = QtConcurrent::run(initialConditions.get(), &ST::diveInto);
    watcher.setFuture(future);
}

void ExperimentParams::futureFinished()
{
    result = watcher.result();
    status = done;
    emit computationFinished(this);
}


bool ExperimentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    emit beginInsertRows(QModelIndex(),
                         index.row(), index.row());
    auto insertIter = experiments.begin() += index.row();
    ExperimentParams* item = value.value<ExperimentParams*>();

        //TODO: Childrens handling!
        experiments.insert(insertIter, item);

        //emit dataChanged(index, index, {role});
        emit endInsertRows();
        return true;

}
