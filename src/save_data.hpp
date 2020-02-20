#ifndef SAVE_DATA_HPP
#define SAVE_DATA_HPP
/*  -*- coding: utf-8 -*-  */
#include <QString>
#include <QDate>

namespace libif { class SaveDataUser; }

class libif::SaveDataUser{
public:
    QString surname;            /* Фамилия */
    QString name;               /* Имя */
    QString patronymic;         /* Отчество */
    int32_t year{0};            /* Лет */

    QString group;

    QString time_of_day;        /* время суток */
    QDate date;                 /* дата */
    QString day_week;           /* день недели */

    int32_t count_test{0};

    /* correct answer */
    int32_t summ_correct_time{0};
    int32_t n_correct{0};

    inline void increment_correct_answer() noexcept{ ++n_correct; return; }

    inline void increment_test() noexcept{ ++count_test; return; }
};/* end class SaveDataUser */


#endif // SAVE_DATA_HPP
