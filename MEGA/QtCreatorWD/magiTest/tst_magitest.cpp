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
    auto simulationConstants = std::make_shared<SimulationConstants>(ui->stepUSpinBox->value(), ui->nEpochsSpinBox->value());
    auto capitalFunction  = std::make_shared<CapitalFunction>(ui->deltaSpinBox->value(), ui->savingSpinBox->value());
    auto productionFunction  = std::make_shared<ProductionFunction>(ui->regASpinBox->value(), ui->regP1SpinBox->value(),
                                                                    ui->regP2SpinBox->value(), ui->exportSpinBox->value(), ui->woodProductionSpinBox->value());
    auto costFunction  = std::make_shared<CostFunction>(ui->CostSpinBox->value(), ui->savingSpinBox->value());

    auto initialConditions = std::make_shared<ST>(ui->ProductionSpinBox->value(), ui->capitalSpinBox->value(),
                         Proportion::makeNewProportionFromAX(ui->aSpinBox->value(), ui->xSpinBox->value()), 0, 0,
              simulationConstants, capitalFunction, productionFunction, costFunction);
}

void MagiTest::serializationTest_data()
{
    using namespace QTest;
    auto columns = QVector<const char*> { "stepU", "nEpochs", "delta", "saving", "regA", "regP1", "regP2", "export", "wood", "cost",
            "production", "capital", "a", "x"};
    std::for_each(columns.begin(), columns.end(), [](auto t){ return addColumn<double>(t); });
    QTestData& rowOne = newRow("ones");
    std::for_each(columns.begin(), columns.end(), [&rowOne](auto str){
        (rowOne << 1.0);
    });
}

QTEST_APPLESS_MAIN(MagiTest)

#include "tst_magitest.moc"
