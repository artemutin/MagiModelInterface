#ifndef COMMON_CONSTANTS_HPP
#define COMMON_CONSTANTS_HPP

#include <QString>
#include <map>

namespace Consts{
//Колонки таблиц моделей QT mv-фреймворка
enum Columns{
        x,
        result,
        production,
        capital,
        a,
        b,
        alpha,
        status,
        stepU,
        nTiers,
        delta,
        savings,
        regA,
        regP1,
        regP2,
        woodProduction,
        exportCost,
        cost,
         tier,
         controlParameter
    };

   const std::map<Columns, QString> Labels = {
       {x, "x"                           },
       {result, "Цел. функция"           },
       {production, "ВВП отрасли"        },
       {capital, "Капитал"               },
       {a, "а"                           },
       {b, "b"                           },
       {alpha, "\u03B1"                  },
       {status, "Статус"                 },
       {stepU, "Шаг u"                   },
       {nTiers, "Число этапов"           },
       {delta, "\u03B4"                  },
       {savings, "Доля инвестиций"       },
       {regA, "А"                        },
       {regP1, "p1"                      },
       {regP2, "p2"                      },
       {woodProduction, "Объем заготовки"},
       {exportCost, "Экспортная цена"    },
       {cost, "Цена преобразований"      },
       { tier, "Этап"                    },
       { controlParameter, "u"           },
};
}


#endif // COMMON_CONSTANTS_HPP
