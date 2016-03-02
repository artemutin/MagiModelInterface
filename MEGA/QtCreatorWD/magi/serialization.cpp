#include "serialization.hpp"

QDataStream &operator<<(QDataStream & os, const SimulationTier & st)
{
        os << st.production << st.capital << st.proportion << st.tier << st.result << st.alpha <<
              st.controlParameter << *st.simConstants << *st.capitalFunction << *st.productionFunction <<
              *st.costFunction;

        return os;
}

QDataStream &operator<<(QDataStream & os, const Proportion & prop)
{
    os << prop.a << prop.b << prop.x;
    return os;
}

QDataStream &operator<<(QDataStream & os, const SimulationConstants & c)
{
    os << c.stepU << c.numEpochs;
    return os;
}

QDataStream &operator<<(QDataStream &os, const CapitalFunction & c)
{
    os << c.delta << c.savings;
    return os;
}

QDataStream &operator<<(QDataStream &os, const ProductionFunction & pf)
{
    os << pf.rf << pf.ef << pf.woodProduction;
    return os;
}

QDataStream &operator<<(QDataStream &os, const RefactorFunction & rf)
{
    os << rf.a << rf.p1 << rf.p2;
    return os;
}

QDataStream &operator<<(QDataStream &os, const ExportFunction & ef)
{
    os << ef.e;
    return os;
}

QDataStream &operator<<(QDataStream &os, const CostFunction & cf)
{
    os << cf.c << cf.saving;
    return os;
}
