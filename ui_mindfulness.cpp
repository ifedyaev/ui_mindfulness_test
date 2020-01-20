#include "ui_mindfulness.hpp"
#include "ui_ui_mindfulness.h"
#include <QRegExpValidator>
#include <QMessageBox>
#include <QMap>

static constexpr int32_t C_IDX_REGI = 0;
static constexpr int32_t C_IDX_TIME = 1;
static constexpr int32_t C_IDX_INFO = 2;
static constexpr int32_t C_IDX_TEST = 3;
static constexpr int32_t C_IDX_RESU = 4;

static const QString ERR_TITLE = "Ошибка вводимых параметров";
static const QString ERR_FNAME = "Не введена Фамилия";
static const QString ERR_SNAME = "Не введено Имя";
static const QString ERR_GROUP = "Не ведена группа";

static const QStringList C_LIST_WEAK = {
    "Понеденьник",
    "Вторник",
    "Среда",
    "Четверг",
    "Пятница",
    "Суббота",
    "Воскресенье"
};

static const QStringList C_LIST_TD = {
    "Утро",
    "Обед",
    "Вечер"
};

static const QStringList C_LIST_TT = {
    "1 мин.",
    "2 мин.",
    "3 мин."
};

UiMindfulness::UiMindfulness(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UiMindfulness)
{
    ui->setupUi(this);

    /* registation */
    setup_registation();
    /* time */
    setup_time();

}

UiMindfulness::~UiMindfulness()
{
    delete ui;
}


void UiMindfulness::on_push_button_reg_next_clicked()
{
    /* check exists */
    /* first name */
    if(ui->m_line_edit_fn->text() == ""){
        err_message(ERR_FNAME);
        return;
    }
    /* second name */
    if(ui->m_line_edit_sn->text() == ""){
        err_message(ERR_SNAME);
        return;
    }
    /* check group */
    if(ui->m_line_edit_group->text() == ""){
        err_message(ERR_GROUP);
        return;
    }
    /* save data */
    m_save_data.first_name = ui->m_line_edit_fn->text();
    m_save_data.second_name = ui->m_line_edit_sn->text();
    m_save_data.third_name = ui->m_line_edit_tn->text();
    m_save_data.year = ui->m_spin_box_years->value();

    /* unmute time test and mute regisgtation */
    constexpr bool is_enable = true;
    ui->main_tab_widget->setTabEnabled(C_IDX_TIME,is_enable);
    ui->main_tab_widget->setTabEnabled(C_IDX_REGI,not is_enable);

    return;
}

void UiMindfulness::setup_registation()
{
    /* f|s|t name */
    QRegExp rx_rus("[А-Я][а-я]+");
    ui->m_line_edit_fn->setValidator(new QRegExpValidator(rx_rus));
    ui->m_line_edit_sn->setValidator(new QRegExpValidator(rx_rus));
    ui->m_line_edit_tn->setValidator(new QRegExpValidator(rx_rus));
    /* group */

    /* mute tab */
    constexpr bool is_enable = false;
    ui->main_tab_widget->setTabEnabled(C_IDX_TIME,is_enable);
    ui->main_tab_widget->setTabEnabled(C_IDX_INFO,is_enable);
    ui->main_tab_widget->setTabEnabled(C_IDX_TEST,is_enable);
    ui->main_tab_widget->setTabEnabled(C_IDX_RESU,is_enable);
}

void UiMindfulness::setup_time()
{
    QDate now_data = QDate::currentDate();
    QTime now_time = QTime::currentTime();
    /* time day */
    ui->m_combo_box_time_day->addItems(C_LIST_TD);
    const int32_t now_hour = now_time.hour();
    if(now_hour >= 0 and now_hour < 12){
        ui->m_combo_box_time_day->setCurrentIndex(0);
    }
    else if(now_hour >= 12 and now_hour < 18){
        ui->m_combo_box_time_day->setCurrentIndex(1);
    }
    else{
        ui->m_combo_box_time_day->setCurrentIndex(2);
    }

    /* date */
    ui->m_date_edit_time->setDate(now_data);

    /* day weak */
    ui->m_combo_box_weak_day->addItems(C_LIST_WEAK);
    const int32_t idx_weak_day = now_data.dayOfWeek();
    ui->m_combo_box_weak_day->setCurrentIndex(idx_weak_day - 1);
    /* test time */
    ui->m_combo_box_time_test->addItems(C_LIST_TT);

    return;
}

void UiMindfulness::err_message(const QString& err_str) const
{
    QMessageBox::critical(NULL,ERR_TITLE,err_str,
                          QMessageBox::Ok,
                          QMessageBox::Cancel);
    return;
}

void UiMindfulness::on_push_button_time_next_clicked()
{
    m_save_data.idx_time_day = ui->m_combo_box_time_day->currentIndex();
    m_save_data.date = ui->m_date_edit_time->date();
    m_save_data.idx_weak = ui->m_combo_box_weak_day->currentIndex();
    m_save_data.idx_time_test = ui->m_combo_box_time_test->currentIndex();

    /* unmute information test and mute time test */
    constexpr bool is_enable = true;
    ui->main_tab_widget->setTabEnabled(C_IDX_INFO,is_enable);
    ui->main_tab_widget->setTabEnabled(C_IDX_TIME,not is_enable);

    return;
}

void UiMindfulness::on_m_push_button_info_clicked()
{
    /* unmute Test and mute information test */
    constexpr bool is_enable = true;
    ui->main_tab_widget->setTabEnabled(C_IDX_TEST,is_enable);
    ui->main_tab_widget->setTabEnabled(C_IDX_INFO,not is_enable);
    return;
}
