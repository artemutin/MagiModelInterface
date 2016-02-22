#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <cmath>
#include <list>

//outer constants, determining parameters of simulation
struct SimulationConstants {
    double stepU;
    int numEpochs;
    SimulationConstants(double stepU, int numEpochs):stepU(stepU), numEpochs(numEpochs){}
};

//inner model constants, dont change in simulation run
struct CapitalFunction {
    double delta;
    double savings;

    CapitalFunction(double delta, double savings):delta(delta), savings(savings){}
    double operator() (const double& capital, const double& production,
                       const double& controlParameter) const;
};

//yet another inner model constants
class RefactorFunction  {
    double a;
    double p1;
    double p2;

public:
    RefactorFunction(double a, double p1, double p2):a(a), p1(p1), p2(p2){}
    double operator() (const double& capital, const double& refactoredWood) const;
};

//export cost and overall raw wood production, for now also constants
struct ExportFunction {
    const double e;
    ExportFunction(double e):e(e){}
    double operator() (const double& exportedWood) const;
};

class Proportion; class SimulationTier;

struct ProductionFunction{
    RefactorFunction rf;
    ExportFunction ef;
    double woodProduction;

    ProductionFunction(double a, double p1, double p2, double exportCost, double woodProduction):
        rf(a, p1, p2), ef(exportCost), woodProduction(woodProduction){}
    double operator() (const double& capital, const Proportion& prop) const;
};

class Proportion {
    static double calcProp(const double& a, const double& b);
    static double calcB(const double& a, const double& x);
    Proportion(const double& a, const double& b, const double& x):a(a), b(b), x(x){}

public:
    double a, b; // transform matrix elements
    double x; //actual prop of refactored wood

    static Proportion makeNewProportionFromAB(const double& a, const double& b);
    static Proportion makeNewProportionFromAX(const double& a, const double& x);
    double operator[] (std::size_t i) const; //get props x_1 and x_2
    Proportion makeNewProportionFromAlpha(const double& alpha) const;
    Proportion(){}//bad, bad empty construction shit
};

struct CostFunction {
    double c, saving;

    CostFunction(double c, double saving):c(c), saving(saving){}
    double operator() (const double& controlParameter, const double& production) const;
};

struct FirstSimulationTier {
    double production, capital;//current production and capital
    Proportion proportion;
    int tier;//what tier of simulation it is
    double result;//result of the tier - summary production, or whatever;

    std::shared_ptr<SimulationConstants> simConstants;
    std::shared_ptr<CapitalFunction> capitalFunction;
    std::shared_ptr<ProductionFunction> productionFunction;
    std::shared_ptr<CostFunction> costFunction;

    std::list<SimulationTier> diveInto();
    //polymorfic hack for adding to queue list
    virtual void addMyselfToList(std::list<SimulationTier>& ref );

    double computeResult(const FirstSimulationTier& prevRes);

    FirstSimulationTier(const double& production, const double& capital, const Proportion& prop,
                        const double& result, const int& tier,
                        std::shared_ptr<SimulationConstants> simConstants,
                        std::shared_ptr<CapitalFunction> capitalFunction,
                        std::shared_ptr<ProductionFunction> productionFunction,
                        std::shared_ptr<CostFunction> costFunction);
    FirstSimulationTier(){}
};
typedef FirstSimulationTier FST;

struct SimulationTier: public FirstSimulationTier{
    double alpha;
    double controlParameter;

    SimulationTier(const FirstSimulationTier& prev, double controlParameter);

    virtual void addMyselfToList(std::list<SimulationTier>& ref );
};
typedef SimulationTier ST;


#endif // MODEL_HPP
