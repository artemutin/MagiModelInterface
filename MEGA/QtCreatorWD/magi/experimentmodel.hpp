#ifndef EXPERIMENTMODEL_HPP
#define EXPERIMENTMODEL_HPP

#include <QAbstractItemModel>
#include "model.hpp"
#include "common_constants.hpp"

class ExperimentModel : public QAbstractItemModel
{

    Q_OBJECT

    enum ExperimentStatus {
        notStarted,
        inProgress,
        done
    };


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
};

#endif // EXPERIMENTMODEL_HPP
