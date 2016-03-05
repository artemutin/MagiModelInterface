#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <cmath>
#include <list>

//outer constants, determining parameters of simulation
struct SimulationConstants {
    double stepU;
    int numEpochs;
    SimulationConstants(){}//serialization only
    SimulationConstants(double stepU, int numEpochs):stepU(stepU), numEpochs(numEpochs){}

    bool operator == (const SimulationConstants & a) const;
};

//inner model constants, dont change in simulation run
struct CapitalFunction {
    double delta;
    double savings;

    CapitalFunction(double delta, double savings):delta(delta), savings(savings){}
    CapitalFunction(){}//serialization only
    double operator() (const double& capital, const double& production,
                       const double& controlParameter) const;

    bool operator== (const CapitalFunction& a);
};

//yet another inner model constants
struct RefactorFunction  {
    double a;
    double p1;
    double p2;

    RefactorFunction(){}//serializ
    RefactorFunction(double a, double p1, double p2):a(a), p1(p1), p2(p2){}
    double operator() (const double& capital, const double& refactoredWood) const;
    bool operator== (const RefactorFunction& a) const;
};

//export cost and overall raw wood production, for now also constants
struct ExportFunction {
    double e;
    ExportFunction(){}//serial only
    ExportFunction(double e):e(e){}
    double operator() (const double& exportedWood) const;
    bool operator==(const ExportFunction& a) const;
};

class Proportion; class SimulationTier;

struct ProductionFunction{
    RefactorFunction rf;
    ExportFunction ef;
    double woodProduction;

    ProductionFunction(){}//serialization only
    ProductionFunction(double a, double p1, double p2, double exportCost, double woodProduction):
        rf(a, p1, p2), ef(exportCost), woodProduction(woodProduction){}
    double operator() (const double& capital, const Proportion& prop) const;
    bool operator ==(const ProductionFunction& a);
};

class Proportion {
    static double calcProp(const double& a, const double& b);

    Proportion(const double& a, const double& b, const double& x):a(a), b(b), x(x){}

public:
    double a, b; // transform matrix elements
    double x; //actual prop of refactored wood
    //used in form validation
    static double calcB(const double& a, const double& x);
    static Proportion makeNewProportionFromAB(const double& a, const double& b);
    static Proportion makeNewProportionFromAX(const double& a, const double& x);
    double operator[] (std::size_t i) const; //get props x_1 and x_2
    Proportion makeNewProportionFromAlpha(const double& alpha) const;
    Proportion(){}//bad, bad empty construction shit
    bool operator ==(const Proportion& a) const;
};

struct CostFunction {
    double c, saving;

    CostFunction(){}//for serialization
    CostFunction(double c, double saving):c(c), saving(saving){}
    double operator() (const double& controlParameter, const double& production) const;
    bool operator== (const CostFunction& a) const;
};

struct SimulationTier;
typedef SimulationTier ST;
typedef std::list<SimulationTier> Result;
typedef std::shared_ptr<Result> ResultPtr;

struct SimulationTier {
    double production, capital;//current production and capital
    Proportion proportion;
    int tier;//what tier of simulation it is
    double result;//result of the tier - summary production, or whatever;
    double alpha;
    double controlParameter;

    std::shared_ptr<SimulationConstants> simConstants;
    std::shared_ptr<CapitalFunction> capitalFunction;
    std::shared_ptr<ProductionFunction> productionFunction;
    std::shared_ptr<CostFunction> costFunction;

    ResultPtr diveInto();

    double computeResult(const SimulationTier& prevRes);

    SimulationTier(const double& production, const double& capital, const Proportion& prop,
                        const double& result, const int& tier,
                        std::shared_ptr<SimulationConstants> simConstants,
                        std::shared_ptr<CapitalFunction> capitalFunction,
                        std::shared_ptr<ProductionFunction> productionFunction,
                        std::shared_ptr<CostFunction> costFunction);
    SimulationTier(){}
    SimulationTier(const SimulationTier& a);
    SimulationTier(const SimulationTier& prev, double controlParameter);
    bool operator== (const SimulationTier& a ) const;
};


#endif // MODEL_HPP
