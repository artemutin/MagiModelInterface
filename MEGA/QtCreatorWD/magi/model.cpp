#include "model.hpp"
#include <iostream>

double RefactorFunction::operator()(const double &capital, const double &resource) const
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

double ProductionFunction::operator()(const double &capital, const Proportion &prop) const
{
    return ef(prop[1]*woodProduction) + rf(capital, prop[2]*woodProduction);
}

typedef FirstSimulationTier FST;

SimulationTier::SimulationTier(const FirstSimulationTier &prev, double controlParameter): FirstSimulationTier(prev),
  controlParameter(controlParameter)
{
    FST::tier = prev.tier + 1;
    //since last year, the amount of capital of industry has changed due to investments and amortisation
    capital = (*FST::capitalFunction)(prev.capital, prev.production, controlParameter);
    //also we bought some lobby from last years investment budget
    alpha = (*FST::costFunction)(controlParameter, prev.production);
    //this lobby has changed a proportion of wood production
    proportion = prev.proportion.makeNewProportionFromAlpha(alpha);
    //changed proportion and capital affects a production, ofcourse
    production = (*FST::productionFunction)(capital, proportion);
    //and we can finally compute a result function
    result = FirstSimulationTier::computeResult(prev);
}

void SimulationTier::addMyselfToList(ResultPtr ref)
{
    ref->push_back(*this);
}

ResultPtr FirstSimulationTier::diveInto()
{
    std::cout << "In tier:" << tier << std::endl;
    if (tier == FST::simConstants->numEpochs){
        ResultPtr list = ResultPtr(new Result);
        addMyselfToList(list);
        return list;
    }else{
        auto max_result = -1;
        ResultPtr bestList;

        for (double u = 0; u <= 1; u += FST::simConstants->stepU){
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
        addMyselfToList(bestList);
        return bestList;
    }
}

void FirstSimulationTier::addMyselfToList(ResultPtr ref)
{
}


double FirstSimulationTier::computeResult(const FirstSimulationTier &prev)
{
    return production + prev.production;
}

FirstSimulationTier::FirstSimulationTier(const double &production, const double &capital, const Proportion &prop, const double &result, const int &tier, std::shared_ptr<SimulationConstants> simConstants, std::shared_ptr<CapitalFunction> capitalFunction, std::shared_ptr<ProductionFunction> productionFunction, std::shared_ptr<CostFunction> costFunction):production(production), capital(capital), proportion(prop), result(result), tier(tier),
    simConstants(simConstants), capitalFunction(capitalFunction), productionFunction(productionFunction),
    costFunction(costFunction)
{

}
