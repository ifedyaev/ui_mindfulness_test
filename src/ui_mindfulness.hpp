#ifndef UIMINDFULNESS_HPP
#define UIMINDFULNESS_HPP
/* coding utf-8
 * Программа для проведения теста на внимательность.
 * Автор:       Федяев Игорь
 * Автор Идеи:  Мухутдинова Нейля
 * Дата окночания написания: 23.01.2020 г.
 */

#include <QMainWindow>
#include <QGraphicsScene>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class UiMindfulness; }
QT_END_NAMESPACE

namespace libif {
class SaveDataUser;
class GraphicsView;
}

#include "save_data.hpp"
class GraphicsView;

class UiMindfulness : public QMainWindow
{
    Q_OBJECT

public:
    UiMindfulness(QWidget *parent = nullptr);
    ~UiMindfulness() = default;

    void keyPressEvent(QKeyEvent* ev);

private slots:
    void on_push_button_reg_next_clicked();

    void on_push_button_time_next_clicked();

    void on_m_push_button_info_clicked();

    void on_m_push_button_save_clicked();

    /**
     * @brief update_timer slot update timer
     */
    void update_timer();

private:

    std::shared_ptr<Ui::UiMindfulness> ui;     /* GUI */

    /* graphics view */
    std::shared_ptr<GraphicsView> m_view;      /* graphics view square */
    std::shared_ptr<QGraphicsScene> m_scren;   /* scene view in graphics view */

    /* save data test */
    libif::SaveDataUser m_save_data;            /* save data test user */

    /* measuring test */
    QTime m_time_test;                          /* timer all test */
    int32_t m_test_ms{0};                       /* save time test to ms */
    QColor m_color_save;                        /* color now view square */

    QTime m_one_test;                           /* time test */

    /* timer test */
    std::shared_ptr<QTimer> m_timer_test;       /* timer start -> run test */
    int32_t m_max_test_sec{0};                  /* set second test */

private:
    /**
     * @brief setup_registation init registration tab
     */
    void setup_registation();

    /**
     * @brief setup_time init time test view tab
     */
    void setup_time();

    /**
     * @brief setup_test init test data view tab
     */
    void setup_test();

    /**
     * @brief setup_result init test result view tab
     */
    void setup_result();

    /**
     * @brief err_message set error message from user
     * @param err_str message error
     */
    void err_message(const QString& err_str) const;

    /**
     * @brief set_new_square set new square to view window
     */
    void set_new_square();

    /**
     * @brief start_test init all data to start test
     */
    void start_test();

    /**
     * @brief end_test clear all data to start test
     */
    void end_test();

    /**
     * @brief update_lable
     * @param number
     */
    inline void update_lable(const int32_t number);

    /**
     * @brief set_mute_unmute_tab set mute tab and unmute second tab
     * @param idx_mute
     * @param idx_unmute
     */
    void set_mute_unmute_tab(const int32_t idx_mute,const int32_t idx_unmute);

    /**
     * @brief to_title  convert QString to title
     * @param str       input QString
     * @return
     */
    inline QString to_title(const QString& str) const noexcept;

    /**
     * @brief second_to_time convert second to QTimer
     * @param second input second
     * @return QTimer
     */
    inline QTime second_to_time(const int32_t second) const noexcept;


    inline QString str_to_utf8(const QString& str)const noexcept;
};
#endif // UIMINDFULNESS_HPP
