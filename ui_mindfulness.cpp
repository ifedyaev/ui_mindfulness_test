#include "ui_mindfulness.hpp"
#include "ui_ui_mindfulness.h"
#include <QRegExpValidator>
#include <QMessageBox>
#include <QPainter>
#include <QPolygon>
#include <QKeyEvent>
#include <QColor>
#include <QGraphicsItem>
#include <QSizePolicy>
#include <QTableWidget>

#include <QDebug>

#include <random>

#include "graphics_view.hpp"

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
    "День",
    "Вечер"
};

static const QStringList C_LIST_TT = {
    "1 мин.",
    "2 мин.",
    "3 мин."
};

static const QStringList C_LIST_HDR = {
    "Наименование",
    "Конечные данные"
};

static const QStringList C_LIST_ROW = {
    "Фамилия",
    "Имя",
    "Отчество",
    "Возраст",
    "Группа",
    "Время Суток",
    "Дата",
    "День Недели",
    "Время затраченное на тест ( ms )",
    "Количество правельных ответов",
    "Количество не правельных ответов",
    "Среднее время потраченное на Правельный ответ ( ms )"
};

static const int32_t C_MAX_TEST = 10;

static const QString C_MAX_TEST_STR = QString().sprintf("%03d", C_MAX_TEST);

UiMindfulness::UiMindfulness(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UiMindfulness)
{
    ui->setupUi(this);

    /* registation */
    setup_registation();
    /* time */
    setup_time();
    /* test frame */
    setup_test();
    /* result */
    setup_result();
}

UiMindfulness::~UiMindfulness()
{
    delete ui;
    delete m_scren;
}

void UiMindfulness::keyPressEvent(QKeyEvent *ev)
{
    if(ui->m_main_tab_widget->currentIndex() != C_IDX_TEST){
        return;
    }

    const int32_t key = ev->key();
    if( key == Qt::Key_Space ){
        qDebug() << "Space -> " << key;
        if(m_color_save == QColor(Qt::red)){
            m_save_data.increment_correct_answer();
            m_save_data.summ_correct_time += m_one_test.restart();
        }
        set_new_square();
    }
    else if(key == Qt::Key_Enter or key == Qt::Key_Return){
        qDebug() << "Enter -> " << key;
        if(m_color_save == QColor(Qt::blue)){
            m_save_data.increment_correct_answer();
            m_save_data.summ_correct_time += m_one_test.restart();
        }
        set_new_square();
    }
    else{
//        QDialog::keyPressEvent(ev);
    }
    return;
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
    m_save_data.first_name  = ui->m_line_edit_fn->text();
    m_save_data.second_name = ui->m_line_edit_sn->text();
    m_save_data.third_name  = ui->m_line_edit_tn->text();
    m_save_data.year        = ui->m_spin_box_years->value();
    m_save_data.group       = ui->m_line_edit_group->text();

    /* unmute time test and mute regisgtation */
    constexpr bool is_enable = true;

    ui->m_main_tab_widget->setTabEnabled(C_IDX_TIME,is_enable);
    ui->m_main_tab_widget->setTabEnabled(C_IDX_REGI,not is_enable);

    return;
}

void UiMindfulness::setup_registation()
{
    /* f|s|t name */
    const QRegExp rx_rus("[А-Я][а-я]+");
    ui->m_line_edit_fn->setValidator(new QRegExpValidator(rx_rus));
    ui->m_line_edit_sn->setValidator(new QRegExpValidator(rx_rus));
    ui->m_line_edit_tn->setValidator(new QRegExpValidator(rx_rus));
    /* group */

    /* mute tab */
    constexpr bool is_enable = false;
    ui->m_main_tab_widget->setTabEnabled(C_IDX_TIME,is_enable);
    ui->m_main_tab_widget->setTabEnabled(C_IDX_INFO,is_enable);
    ui->m_main_tab_widget->setTabEnabled(C_IDX_TEST,is_enable);
    ui->m_main_tab_widget->setTabEnabled(C_IDX_RESU,is_enable);
    return;
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

void UiMindfulness::setup_test()
{
    m_view = new libif::GraphicsView(ui->widget);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->addWidget(m_view);

    ui->widget->setLayout(layout);

    m_scren = new QGraphicsScene(this);
    m_scren->setSceneRect(QRectF(0.0, 0.0, 1000.0, 1000.0));

    m_view->setScene(m_scren);
    m_view->setViewRect(m_scren->sceneRect());

    return;
}

void UiMindfulness::setup_result()
{
    QTableWidget& tw_res = *ui->m_table_widget_result;
    int32_t i;

    const int32_t n_col = static_cast<int32_t>(C_LIST_HDR.size());
    /* set header */
    tw_res.setColumnCount(n_col);
    tw_res.setHorizontalHeaderLabels(C_LIST_HDR);
    for(i = 0; i < n_col; ++i){
        tw_res.horizontalHeaderItem(i)->setTextAlignment(Qt::AlignCenter);
    }
    tw_res.horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tw_res.horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    const int32_t n_row = static_cast<int32_t>(C_LIST_ROW.size());
    tw_res.setRowCount(n_row);
    for(i = 0; i < n_row; ++i){
        /* first */
        QTableWidgetItem* item = new QTableWidgetItem(C_LIST_ROW[i]);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        tw_res.setItem(i,0,item);
        /* second */
        item = new QTableWidgetItem("");
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        tw_res.setItem(i,1,item);
    }

    ui->m_time_edit_test->setEnabled(false);
    return;
}

void UiMindfulness::err_message(const QString& err_str) const
{
    QMessageBox::critical(NULL,ERR_TITLE,err_str,
                          QMessageBox::Ok,
                          QMessageBox::Cancel);
    return;
}

void UiMindfulness::set_new_square()
{
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_int_distribution<int> dist(0,1);

    const int32_t idx_rand = dist(e2);

    if(idx_rand == 0){
        m_color_save = Qt::red;
        ui->statusbar->showMessage("Красный");
    }
    else{
        m_color_save = Qt::blue;
        ui->statusbar->showMessage("Голубой");
    }
    const int32_t line_width = 1;
    const QPen c_pen = QPen(Qt::black, line_width, Qt::SolidLine, Qt::FlatCap);
    const QBrush c_brush = QBrush(m_color_save, Qt::SolidPattern);

    const int32_t n_items = m_view->items().size();

    if(n_items == 0){
        m_scren->addRect(250.0, 250.0, 500.0, 500.0, c_pen, c_brush);
    }
    else{
        QGraphicsRectItem* sq_item = static_cast<QGraphicsRectItem*>(m_view->items().first());
        sq_item->setRect(250.0, 250.0, 500.0, 500.0);
        sq_item->setPen(c_pen);
        sq_item->setBrush(c_brush);
    }

    m_one_test.restart();

    if(m_save_data.count_test == C_MAX_TEST){
        end_test();
        return;
    }
    m_save_data.increment_test();
    update_lable(m_save_data.count_test);

    return;
}

void UiMindfulness::end_test()
{
    /* unmute information test and mute time test */
    constexpr bool is_enable = true;
    ui->statusbar->showMessage("");
    ui->m_main_tab_widget->setTabEnabled(C_IDX_RESU,is_enable);
    ui->m_main_tab_widget->setTabEnabled(C_IDX_TEST,not is_enable);
    m_test_ms = m_time_test.elapsed();
    /* set data */
    const int32_t col_answer = 1;

    /* set name */
    QTableWidget& tw_res = *ui->m_table_widget_result;

    tw_res.item(0,col_answer)->setText(m_save_data.first_name);
    tw_res.item(1,col_answer)->setText(m_save_data.second_name);
    tw_res.item(2,col_answer)->setText(m_save_data.third_name);
    tw_res.item(3,col_answer)->setText(QString::number(m_save_data.year));
    tw_res.item(4,col_answer)->setText(m_save_data.group);
    tw_res.item(5,col_answer)->setText(m_save_data.time_day);
    tw_res.item(6,col_answer)->setText(m_save_data.date.toString());
    tw_res.item(7,col_answer)->setText(m_save_data.day_weak);

    tw_res.item(8,col_answer)->setText(QString::number(m_test_ms));
    tw_res.item(9,col_answer)->setText(QString::number(m_save_data.n_correct));
    tw_res.item(10,col_answer)->setText(QString::number(m_save_data.count_test - m_save_data.n_correct ));
    tw_res.item(11,col_answer)->setText(QString::number( m_save_data.summ_correct_time/static_cast<float>(m_save_data.n_correct) ));

    return;
}

void UiMindfulness::update_lable(const int32_t number)
{
    QString cur_text;
    cur_text.sprintf("%03d", number);
    ui->m_label_result_test->setText(QString("%1 из %2").arg(cur_text,C_MAX_TEST_STR));
    return;
}

void UiMindfulness::on_push_button_time_next_clicked()
{
    m_save_data.time_day      = ui->m_combo_box_time_day->currentText();
    m_save_data.date          = ui->m_date_edit_time->date();
    m_save_data.day_weak      = ui->m_combo_box_weak_day->currentText();
    m_save_data.idx_time_test = ui->m_combo_box_time_test->currentIndex();

    /* unmute information test and mute time test */
    constexpr bool is_enable = true;
    ui->m_main_tab_widget->setTabEnabled(C_IDX_INFO,is_enable);
    ui->m_main_tab_widget->setTabEnabled(C_IDX_TIME,not is_enable);

    return;
}

void UiMindfulness::on_m_push_button_info_clicked()
{
    /* unmute Test and mute information test */
    constexpr bool is_enable = true;
    ui->m_main_tab_widget->setTabEnabled(C_IDX_TEST,is_enable);
    ui->m_main_tab_widget->setTabEnabled(C_IDX_INFO,not is_enable);
    /* set square */
    set_new_square();
    m_time_test.start();
    return;
}
