#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include <QDataStream>
#include "model.hpp"
#include "experimentmodel.hpp"

const int SERIALIZATION_VERSION = 1;
const int MAGIC_NUMBER = 0xBEEF101;


QDataStream &operator>>(QDataStream &, ExperimentStatus &);

QDataStream &operator<<(QDataStream &, const SimulationTier &);
QDataStream &operator>>(QDataStream &, SimulationTier &);

QDataStream &operator<<(QDataStream &, const Proportion &);
QDataStream &operator>>(QDataStream &, Proportion &);

QDataStream &operator<<(QDataStream &, const SimulationConstants &);
QDataStream &operator>>(QDataStream &, SimulationConstants &);

QDataStream &operator<<(QDataStream & os, const CapitalFunction &);
QDataStream &operator>>(QDataStream & os, CapitalFunction &);

QDataStream &operator<<(QDataStream & os, const ProductionFunction &);
QDataStream &operator>>(QDataStream & os, ProductionFunction &);

QDataStream &operator<<(QDataStream & os, const RefactorFunction &);
QDataStream &operator>>(QDataStream & os, RefactorFunction &);

QDataStream &operator<<(QDataStream & os, const ExportFunction &);
QDataStream &operator>>(QDataStream & os, ExportFunction &);

QDataStream &operator<<(QDataStream & os, const CostFunction &);
QDataStream &operator>>(QDataStream & os, CostFunction &);

#endif // SERIALIZATION_HPP
