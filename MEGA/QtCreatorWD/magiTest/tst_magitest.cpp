#include <QString>
#include <QtTest>
#include "../magi/model.hpp"
#include "../magi/serialization.hpp"

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
    void serializationTest();
    void serializationTest_data();
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
    auto simulationConstants = std::make_shared<SimulationConstants>(0.1, 4);
    auto capitalFunction  = std::make_shared<CapitalFunction>(0.95, 0.2);
    auto productionFunction  = std::make_shared<ProductionFunction>(100, 0.7, 0.3, 80, 1e5);
    auto costFunction  = std::make_shared<CostFunction>(1000, 0.2);

    ST* start = new ST(1e6, 1e5, Proportion::makeNewProportionFromAX(0.5, 0.3), 0, 0,
              simulationConstants, capitalFunction, productionFunction, costFunction);
    auto best = start->diveInto();
    int i = 32;
}

void MagiTest::serializationTest()
{

    QFETCH(double, stepU);
    QFETCH(double, nEpochs);
    QFETCH(double, delta);
    QFETCH(double, saving);
    QFETCH(double, regA);
    QFETCH(double, regP1);
    QFETCH(double, regP2);
    QFETCH(double, e);
    QFETCH(double, wood);
    QFETCH(double, cost);
    QFETCH(double, production);
    QFETCH(double, capital);
    QFETCH(double, a);
    QFETCH(double, x);
    auto simulationConstants = std::make_shared<SimulationConstants>(stepU, nEpochs);
    auto capitalFunction  = std::make_shared<CapitalFunction>(delta, saving);
    auto productionFunction  = std::make_shared<ProductionFunction>(regA, regP1,
                                                                    regP2, e, wood);
    auto costFunction  = std::make_shared<CostFunction>(cost, saving);

    auto st = ST(production, capital,
                         Proportion::makeNewProportionFromAX(a, x), 0, 0,
              simulationConstants, capitalFunction, productionFunction, costFunction);
    QFile f("/tmp/ser");
    f.open( QIODevice::WriteOnly);
    QDataStream out(&f);
    out << st;
    f.close();

    f.open(QIODevice::ReadOnly);
    QDataStream in(&f);
    ST deser;
    in >> deser;
    f.close();

    QCOMPARE(st, deser);
}

void MagiTest::serializationTest_data()
{
    using namespace QTest;
    auto columns = QVector<const char*> { "stepU", "nEpochs", "delta", "saving", "regA", "regP1", "regP2", "e", "wood", "cost",
            "production", "capital", "a", "x"};
    std::for_each(columns.begin(), columns.end(), [](auto t){ return addColumn<double>(t); });
    QTestData& rowOne = newRow("ones");
    std::for_each(columns.begin(), columns.end(), [&rowOne](auto str){
        (rowOne << 1.0);
    });
}

QTEST_APPLESS_MAIN(MagiTest)

#include "tst_magitest.moc"
