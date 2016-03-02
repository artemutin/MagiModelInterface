#include "serialization.hpp"

QDataStream &operator<<(QDataStream & os, const SimulationTier & st)
{
        os << st.production << st.capital << st.proportion << st.tier << st.result << st.alpha <<
              st.controlParameter << *st.simConstants << *st.capitalFunction << *st.productionFunction <<
              *st.costFunction;

        return os;
}

QDataStream &operator>>(QDataStream & is, SimulationTier & st)
{
    double production, capital, tier, result, alpha, controlParameter;
    Proportion prop; SimulationConstants simConstants; CapitalFunction capitalFunction;
    ProductionFunction productionFunction; CostFunction costFunction;

    is >> production >> capital >> prop >> tier >> result >> alpha >> controlParameter >>
            simConstants >> capitalFunction >> productionFunction >> costFunction;
    st.production = production;
    st.capital = capital;
    st.proportion = prop;
    st.tier = tier;
    st.result = result;
    st.alpha = alpha;
    st.controlParameter = controlParameter;
    st.simConstants = std::shared_ptr<SimulationConstants>(&simConstants);
    st.capitalFunction = std::shared_ptr<CapitalFunction>(&capitalFunction);
    st.productionFunction = std::shared_ptr<ProductionFunction>(&productionFunction);
    st.costFunction = std::shared_ptr<CostFunction>(&costFunction);
    return is;
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


