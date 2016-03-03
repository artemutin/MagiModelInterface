#include "model.hpp"
#include <QtGlobal>

double RefactorFunction::operator()(const double &capital, const double &resource) const
{
    return a*pow(capital, p1)*pow(resource, p2);
}

bool RefactorFunction::operator==(const RefactorFunction &a) const
{
    return qFuzzyCompare(a.a, this->a) && qFuzzyCompare(a.p1, p1) && qFuzzyCompare(a.p2, p2);
}

double ExportFunction::operator()(const double &N) const
{
    return e*N;
}

bool ExportFunction::operator==(const ExportFunction &a) const
{
    return qFuzzyCompare(a.e, e);
}

double CapitalFunction::operator()(const double &capital, const double &production, const double &controlParameter) const
{
    return delta*capital + (1 - controlParameter)*savings*production;
}

bool CapitalFunction::operator==(const CapitalFunction &a)
{
    return qFuzzyCompare(a.delta, delta) && qFuzzyCompare(a.savings, savings);
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

bool Proportion::operator ==(const Proportion &a) const
{
    return qFuzzyCompare(a.a, this->a) && qFuzzyCompare(a.b, this->b) && qFuzzyCompare(a.x, this->x);
}

double CostFunction::operator()(const double &controlParameter, const double &production) const
{
    auto num = controlParameter*saving*production;
    return num/(c + num);
}

bool CostFunction::operator==(const CostFunction &a) const
{
    return qFuzzyCompare(a.c, c) && qFuzzyCompare(a.saving, saving);
}

double ProductionFunction::operator()(const double &capital, const Proportion &prop) const
{
    return ef(prop[1]*woodProduction) + rf(capital, prop[2]*woodProduction);
}

bool ProductionFunction::operator ==(const ProductionFunction &a)
{
    return a.ef == ef && a.rf == rf;
}

ResultPtr SimulationTier::diveInto()
{
    //std::cout << "In tier:" << tier << std::endl;
    if (tier == ST::simConstants->numEpochs){
        ResultPtr list = ResultPtr(new Result);
        list->push_back(*this);
        return list;
    }else{
        auto max_result = -1;
        ResultPtr bestList;

        for (double u = 0; u <= 1; u += ST::simConstants->stepU){
            //produce next tier with its results
            auto nextTier = SimulationTier(*this, u);
            //but it only produce next level tier and nothing more
            //then we need to dive into further recursion deep, to reach the end
            auto retList = nextTier.diveInto();
            //after floating, we got list with path from bottom to current tier
            //so, if it is best result, that we had, remember it to pass up in callstack
            if (retList->front().result > max_result){
                bestList = retList;
                max_result = retList->front().result;
            }
        }

        //finally, with best result, we pass our list further,
        //and dont forget to add themselves to it
        bestList->push_back(*this);
        return bestList;
    }
}

double SimulationTier::computeResult(const SimulationTier &prev)
{
    return production + prev.production;
}

SimulationTier::SimulationTier(const double &production, const double &capital, const Proportion &prop, const double &result, const int &tier, std::shared_ptr<SimulationConstants> simConstants, std::shared_ptr<CapitalFunction> capitalFunction, std::shared_ptr<ProductionFunction> productionFunction, std::shared_ptr<CostFunction> costFunction):production(production), capital(capital), proportion(prop), tier(tier), result(result),
    simConstants(simConstants), capitalFunction(capitalFunction), productionFunction(productionFunction),
    costFunction(costFunction),alpha(0),controlParameter(0)
{

}

SimulationTier::SimulationTier(const SimulationTier &prev, double controlParameter): SimulationTier(prev)
    {
        this->controlParameter = controlParameter;
        ST::tier = prev.tier + 1;
        //since last year, the amount of capital of industry has changed due to investments and amortisation
        capital = (*ST::capitalFunction)(prev.capital, prev.production, controlParameter);
        //also we bought some lobby from last years investment budget
        alpha = (*ST::costFunction)(controlParameter, prev.production);
        //this lobby has changed a proportion of wood production
        proportion = prev.proportion.makeNewProportionFromAlpha(alpha);
        //changed proportion and capital affects a production, ofcourse
        production = (*ST::productionFunction)(capital, proportion);
        //and we can finally compute a result function
        result = SimulationTier::computeResult(prev);
}

bool SimulationTier::operator==(const SimulationTier &a) const
{
    return qFuzzyCompare(this->alpha, a.alpha) && qFuzzyCompare(this->capital, a.capital) &&
            qFuzzyCompare(this->controlParameter, a.controlParameter) && qFuzzyCompare(this->production, a.production) &&
            qFuzzyCompare(this->result, a.result) && this->tier == a.tier && *capitalFunction == *(a.capitalFunction) &&
            *productionFunction == *(a.productionFunction) && *simConstants == *(a.simConstants) && *costFunction == *(a.costFunction) &&
            a.proportion == proportion;
}

bool SimulationConstants::operator ==(const SimulationConstants &a) const
{
    return a.numEpochs ==numEpochs && qFuzzyCompare(a.stepU, stepU);
}
