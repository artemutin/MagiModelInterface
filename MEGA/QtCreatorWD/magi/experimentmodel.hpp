#ifndef EXPERIMENTMODEL_HPP
#define EXPERIMENTMODEL_HPP

#include <QAbstractItemModel>
#include <QFutureWatcher>
#include "model.hpp"
#include "common_constants.hpp"
#include "resultmodel.hpp"

class ExperimentParams;

enum ExperimentStatus {
    notStarted,
    inProgress,
    done
};

class ExperimentModel : public QAbstractItemModel
{

    Q_OBJECT

    static constexpr Consts::Columns columns[] = {
           Consts::status,
           Consts::stepU,
           Consts::nTiers,
           Consts::delta,
           Consts::savings,
           Consts::regA,
           Consts::regP1,
           Consts::regP2,
           Consts::woodProduction,
           Consts::exportCost,
           Consts::cost,
           Consts::x,
           Consts::result,
           Consts::production,
           Consts::capital,
           Consts::a,
           Consts::b,
        };

    static std::map<int, Consts::Columns> columnByInt;

    std::vector<ExperimentParams*> experiments;
    static constexpr int NCOLS = 1 + 2 + 2 + 5 + 1;

public:
    ExperimentModel(QObject* parent);
    ResultPtr getResult(int row);
    // QAbstractItemModel interface
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    // QAbstractItemModel interface
public:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    virtual bool insertRows(int row, int count, const QModelIndex &parent);
public slots:
    //actualy dives into dfs
    void startExperiment(const QModelIndex&);
    void addExperiment(std::shared_ptr<ST> initialConditions);
    void deleteExperiment(const QModelIndex&);
    void serializeAll(QDataStream& stream);

    //locates model in vector, and emits appropriate dataChanged l
    void computationFinished(ExperimentParams*);
signals:
    void modelEvaluated(std::shared_ptr<ResultModel>);
    void startComputation();





};

//if we will use threads for computations, it means
//that it should be appropriate QObject with signals,
//mb thread support built-in
class ExperimentParams: public QObject{
    Q_OBJECT

    friend class ExperimentModel;
    friend QDataStream& operator <<(QDataStream&, const ExperimentParams&);
    friend QDataStream& operator>>(QDataStream &, ExperimentParams &);
    std::shared_ptr<ST> initialConditions;
    ResultPtr result;
    ExperimentStatus status;
    QFutureWatcher<ResultPtr> watcher;

public:
    ExperimentParams(std::shared_ptr<ST> initialConditions, ExperimentStatus status = notStarted,
                     QObject * parent = 0);

    ExperimentParams(){}
    ~ExperimentParams();

    bool operator ==(const ExperimentParams& p) const;

    ResultPtr getResult() const;

    ExperimentStatus getStatus() const;
    void setStatus(const ExperimentStatus &value);

public slots:
    void startComputation();
private slots:
    void futureFinished();

signals:
    void computationFinished(ExperimentParams*);
};

#endif // EXPERIMENTMODEL_HPP
