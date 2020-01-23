#ifndef UIMINDFULNESS_HPP
#define UIMINDFULNESS_HPP

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
    ~UiMindfulness();

    void keyPressEvent(QKeyEvent* ev);

private slots:
    void on_push_button_reg_next_clicked();

    void on_push_button_time_next_clicked();

    void on_m_push_button_info_clicked();

    void on_m_push_button_save_clicked();

private:

    Ui::UiMindfulness *ui{nullptr};     /* GUI */

    /* graphics view */
    GraphicsView* m_view{nullptr};      /* graphics view square */
    QGraphicsScene* m_scren{nullptr};   /* scene view in graphics view */

    libif::SaveDataUser m_save_data;    /* save data test user */
    QColor m_color_save;                /* color now view square */

    QTime m_time_test;                  /* */
    int32_t m_test_ms{0};               /* */

    QTime m_one_test;                   /* time test */

    QTimer* m_timer_test;

    int32_t m_max_test_sec{0};


private:
    /**
     * @brief setup_registation init registration tab
     */
    void setup_registation();

    /**
     * @brief setup_time init time test
     */
    void setup_time();

    /**
     * @brief setup_test
     */
    void setup_test();

    /**
     * @brief setup_result
     */
    void setup_result();

    /**
     * @brief err_message set error message from user
     * @param err_str message error
     */
    void err_message(const QString& err_str) const;

    /**
     * @brief set_new_square
     */
    void set_new_square();

    /**
     * @brief start_test
     */
    void start_test();

    /**
     * @brief end_test
     */
    void end_test();

    /**
     * @brief update_lable
     * @param number
     */
    void update_lable(const int32_t number);

    /**
     * @brief set_mute_unmute_tab
     * @param idx_mute
     * @param idx_unmute
     */
    void set_mute_unmute_tab(const int32_t idx_mute,const int32_t idx_unmute);

    inline void update_timer();

    inline QString to_title(const QString& str);

    inline QTime second_to_time(const int32_t second) const;
};
#endif // UIMINDFULNESS_HPP
