#ifndef EXPERIMENTMODEL_HPP
#define EXPERIMENTMODEL_HPP

#include <QAbstractItemModel>
#include "model.hpp"
#include "common_constants.hpp"
#include "resultmodel.hpp"

class ExperimentModel : public QAbstractItemModel
{

    Q_OBJECT

    enum ExperimentStatus {
        notStarted,
        inProgress,
        done
    };

    //if we will use threads for computations, it means
    //that it should be appropriate QObject with signals,
    //mb thread support built-in
    struct ExperimentParams{
        std::shared_ptr<FST> initialConditions;
        ExperimentStatus status;
    };

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

    std::vector<ExperimentParams> experiments;
    static constexpr int NCOLS = 1 + 2 + 2 + 5 + 1;

public:
    ExperimentModel();

    // QAbstractItemModel interface
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    // QAbstractItemModel interface
public:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual bool insertRows(int row, int count, const QModelIndex &parent);
public slots:
    void startExperiment(std::shared_ptr<FST> initialConditions);
signals:
    void modelEvaluated(std::shared_ptr<ResultModel>);


};

#endif // EXPERIMENTMODEL_HPP
