#include "model.hpp"


double ProductionFunction::operator()(const double &capital, const double &resource) const
{
    return a*pow(capital, p1)*pow(resource, p2);
}

double ExportFunction::operator()(const double &N) const
{
    return e*N;
}

double CapitalFunction::operator()(const double &capital, const double &production, const double &controlParameter) const
{
    return delta*capital + (1 - controlParameter)*savings*production;
}

double Proportion::calcProp(const double &a, const double &b)
{
    return -(a-1)/(b - a + 1);
}

double Proportion::calcB(const double &a, const double &x)
{
    return ( (a-1)*x - a + 1 )/x;
}

Proportion Proportion::makeNewProportionFromAB(const double &a, const double &b)
{
    return Proportion {a, b, Proportion::calcProp(a, b) };
}

Proportion Proportion::makeNewProportionFromAX(const double &a, const double &x)
{
    return Proportion {a, Proportion::calcB(a, x), x};
}

double Proportion::operator[](std::size_t i) const
{
    switch (i){
    case 1: return 1-x;
    case 2: return x;
    default: throw std::exception();
    }
}

Proportion Proportion::makeNewProportionFromAlpha(const double &alpha) const
{
    auto newA = a*(1-alpha);
    auto newB = b*(1-alpha);
    return Proportion {
                newA, newB, Proportion::calcProp(newA, newB)
    };
}

double CostFunction::operator()(const double &controlParameter, const double &production) const
{
    auto num = controlParameter*saving*production;
    return num/(c + num);
}
