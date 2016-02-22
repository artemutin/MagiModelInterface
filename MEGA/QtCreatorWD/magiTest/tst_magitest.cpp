#include <QString>
#include <QtTest>
#include "../magi/model.hpp"

class MagiTest : public QObject
{
    Q_OBJECT

public:
    MagiTest();

private Q_SLOTS:
    void testCase1();
    void capitalFunction();
    void productionFunction();
    void exportFunction();
    void proportion();
    void costFunction();
    void firstSimulationTier();
};



MagiTest::MagiTest()
{
}

void MagiTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

void MagiTest::capitalFunction()
{
    CapitalFunction cf = CapitalFunction{ 0.95, 0.2 };
    QCOMPARE( cf(100, 200, 0.5), 115.0);
}

void MagiTest::productionFunction()
{
    RefactorFunction pf = RefactorFunction{ 1, 0.4, 0.7 };
    QCOMPARE( pf(1e6, 1e5*0.3), 341967.5353414207);
}

void MagiTest::exportFunction()
{
    ExportFunction ef = ExportFunction{ 80 };
    QCOMPARE( ef(1e5*(1-0.3)), 5600000.0);
}

void MagiTest::proportion()
{
    Proportion p = Proportion::makeNewProportionFromAB(0.3, 0.7);
    QCOMPARE(p.x, 0.5);
    Proportion p1 = Proportion::makeNewProportionFromAX(0.3, 0.7);
    QCOMPARE(p1[1], 0.3);
    QCOMPARE(p1[2], 0.7);
    Proportion p2 = Proportion::makeNewProportionFromAB(p1.a, p1.b);
    QCOMPARE(p1.x, p2.x);
    QCOMPARE(p1.a, p2.a);
    QCOMPARE(p1.b, p2.b);
}

void MagiTest::costFunction()
{
    auto c = CostFunction {1e4, 0.2};
    QCOMPARE( c(0.5, 1e4), 0.0909090909090909 );
}

void MagiTest::firstSimulationTier()
{
    //initializing constants and functions
    auto simulationConstants = std::make_shared<SimulationConstants>(0.1, 0);
    auto capitalFunction  = std::make_shared<CapitalFunction>(0.95, 0.2);
    auto productionFunction  = std::make_shared<ProductionFunction>(100, 0.7, 0.3, 80, 1e5);
    auto costFunction  = std::make_shared<CostFunction>(1000, 0.2);

    FST* start = new FST(1e6, 1e5, Proportion::makeNewProportionFromAX(0.5, 0.3), 0, 0,
              simulationConstants, capitalFunction, productionFunction, costFunction);
    start->diveInto();
}

QTEST_APPLESS_MAIN(MagiTest)

#include "tst_magitest.moc"
