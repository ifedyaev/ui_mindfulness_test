#ifndef SAVE_DATA_HPP
#define SAVE_DATA_HPP
#include <QString>
#include <QDate>

namespace libif { class SaveDataUser; }

class libif::SaveDataUser{
public:
    QString first_name;         /* Фамилия */
    QString second_name;        /* Имя */
    QString third_name;         /* Отчество */
    int32_t year{0};            /* Лет */

    QString group;

    QString time_day;           /* время суток */
    QDate date;                 /* дата */
    QString day_weak;        /* день недели */
    int32_t idx_time_test{0};   /* индекс времени теста */

    int32_t count_test{0};

    /* correct answer */
    int32_t summ_correct_time{0};
    int32_t n_correct{0};

    inline void increment_correct_answer() noexcept{ ++n_correct; return; }

    inline void increment_test() noexcept{ ++count_test; return; }
};/* end class SaveDataUser */


#endif // SAVE_DATA_HPP
