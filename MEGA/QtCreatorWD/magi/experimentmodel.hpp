#ifndef EXPERIMENTMODEL_HPP
#define EXPERIMENTMODEL_HPP

#include <QAbstractItemModel>
#include "model.hpp"

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

    // QAbstractItemModel interface
public:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // EXPERIMENTMODEL_HPP
