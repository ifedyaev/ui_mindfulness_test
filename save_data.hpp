#ifndef SAVE_DATA_HPP
#define SAVE_DATA_HPP
#include <QString>
#include <QDate>

namespace libif {
class SaveDataUser{
public:
    QString first_name;     /* Фамилия */
    QString second_name;    /* Имя */
    QString third_name;     /* Отчество */
    int32_t year;           /* Лет */


    int32_t idx_time_day;   /* индекс время суток */
    QDate date;             /* дата */
    int32_t idx_weak;       /* индекс недели */
    int32_t idx_time_test;  /* индекс времени теста */
};
}

#endif // SAVE_DATA_HPP
