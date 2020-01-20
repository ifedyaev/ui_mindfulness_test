#ifndef UIMINDFULNESS_HPP
#define UIMINDFULNESS_HPP

#include <QMainWindow>

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

private slots:
    void on_push_button_reg_next_clicked();

    void on_push_button_time_next_clicked();

    void on_m_push_button_info_clicked();

private:
    Ui::UiMindfulness *ui;

    libif::SaveDataUser m_save_data;

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
     * @brief err_message set error message from user
     * @param err_str message error
     */
    void err_message(const QString& err_str) const;
};
#endif // UIMINDFULNESS_HPP
