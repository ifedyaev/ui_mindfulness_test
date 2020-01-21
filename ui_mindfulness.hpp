#ifndef UIMINDFULNESS_HPP
#define UIMINDFULNESS_HPP

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class UiMindfulness; }
QT_END_NAMESPACE

#include "save_data.hpp"

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

private:
    Ui::UiMindfulness *ui;

    libif::SaveDataUser m_save_data;

    QColor m_color_save;

    QGraphicsScene* m_scren{nullptr};

    QTime m_time_test;
    int32_t m_test_ms{0};

    QTime m_one_test;
private:
    /**
     * @brief setup_registation init registration tab
     */
    void setup_registation();
    /**
     * @brief setup_time init time test
     */
    void setup_time();

    void setup_test();

    void setup_result();

    /**
     * @brief err_message set error message from user
     * @param err_str message error
     */
    void err_message(const QString& err_str) const;

    void set_new_square();

    void end_test();

    void update_lable(const int32_t number);
};
#endif // UIMINDFULNESS_HPP
