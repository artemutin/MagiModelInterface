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
    double production, capital, result, alpha, controlParameter;
    int tier;
    Proportion prop;
    SimulationConstants* simConstants = new SimulationConstants;
    CapitalFunction* capitalFunction = new CapitalFunction;
    ProductionFunction* productionFunction = new ProductionFunction;
    CostFunction* costFunction = new CostFunction;

    is >> production >> capital >> prop >> tier >> result >> alpha >> controlParameter >>
            *simConstants >> *capitalFunction >> *productionFunction >> *costFunction;
    st.production = production;
    st.capital = capital;
    st.proportion = prop;
    st.tier = tier;
    st.result = result;
    st.alpha = alpha;
    st.controlParameter = controlParameter;
    st.simConstants = std::shared_ptr<SimulationConstants>(simConstants);
    st.capitalFunction = std::shared_ptr<CapitalFunction>(capitalFunction);
    st.productionFunction = std::shared_ptr<ProductionFunction>(productionFunction);
    st.costFunction = std::shared_ptr<CostFunction>(costFunction);
    return is;
}

QDataStream &operator<<(QDataStream & os, const Proportion & prop)
{
    os << prop.a << prop.b << prop.x;
    return os;
}

QDataStream &operator>>(QDataStream &is, Proportion & prop)
{
    double t;
    is >> t;prop.a = t;is >> t; prop.b = t; is >> t; prop.x = t;
    return is;
}

QDataStream &operator<<(QDataStream & os, const SimulationConstants & c)
{
    os << c.stepU << c.numEpochs;
    return os;
}

QDataStream &operator>>(QDataStream & is, SimulationConstants &c)
{
    double t; int n;
    is >> t; c.stepU = t;
    is >> n; c.numEpochs = n;
    return is;
}

QDataStream &operator<<(QDataStream &os, const CapitalFunction & c)
{
    os << c.delta << c.savings;
    return os;
}

QDataStream &operator>>(QDataStream &is, CapitalFunction & c)
{
    double t;
    is >> t; c.delta = t; is >> t; c.savings = t;
    return is;
}

QDataStream &operator<<(QDataStream &os, const ProductionFunction & pf)
{
    os << pf.rf << pf.ef << pf.woodProduction;
    return os;
}

QDataStream &operator>>(QDataStream &is, ProductionFunction &pf)
{
    RefactorFunction rf; ExportFunction ef;
    is >> rf; pf.rf = rf; is >> ef; pf.ef = ef; is >> pf.woodProduction;
    return is;
}

QDataStream &operator<<(QDataStream &os, const RefactorFunction & rf)
{
    os << rf.a << rf.p1 << rf.p2;
    return os;
}

QDataStream &operator>>(QDataStream &is, RefactorFunction & rf)
{
    double t;
    is >> t; rf.a = t; is >> t; rf.p1 = t; is >> t; rf.p2 = t;
    return is;
}

QDataStream &operator<<(QDataStream &os, const ExportFunction & ef)
{
    os << ef.e;
    return os;
}


QDataStream &operator>>(QDataStream &is, ExportFunction &ef)
{
    double t;
    is >> ef.e;
    return is;
}

QDataStream &operator<<(QDataStream &os, const CostFunction & cf)
{
    os << cf.c << cf.saving;
    return os;
}

QDataStream &operator>>(QDataStream &is, CostFunction & cf)
{
    double t;
    is >> cf.c >> cf.saving;
    return is;
}

QDataStream &operator<<(QDataStream &os, const ExperimentParams &p)
{
    QVector<ST> vec(p.result->size());
    std::copy(p.result->begin(), p.result->end(), list.begin());
    os << *(p.initialConditions) << vec << p.status;
    return os;
}
