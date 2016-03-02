#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include <QDataStream>
#include "model.hpp"

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
QDataStream &operator>>(QDataStream & os, const CostFunction &);

#endif // SERIALIZATION_HPP
