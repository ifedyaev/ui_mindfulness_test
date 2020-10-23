/*  -*- coding: utf-8 -*-  */
#include "src/ui_mindfulness.hpp"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    /* set codec utf-8 */
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); //изменения

    QApplication a(argc, argv); /* set args */
    UiMindfulness w;            /* create UI */
    w.showMaximized();          /* show UI */
    return a.exec();            /* wait for the end */
}
