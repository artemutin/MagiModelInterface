#ifndef EXPERIMENTMODEL_HPP
#define EXPERIMENTMODEL_HPP

#include <QAbstractItemModel>
#include "model.hpp"

class ExperimentModel : public QAbstractItemModel
{

    Q_OBJECT

    struct ExperimentParams{
        std::shared_ptr<FST> initialConditions;
        ExperimentStatus status;
    };

    enum ExperimentStatus {
        notStarted,
        inProgress,
        done
    };

    enum Columns {
        status,
        stepU,
        nTiers,
        delta,
        savings,
        regA,
        regP1,
        regP2,
        woodProduction,
        exportCost,
        cost,
        x,
        result,
        production,
        capital,
        a,
        b,
        alpha
    };

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
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);
};

#endif // EXPERIMENTMODEL_HPP
