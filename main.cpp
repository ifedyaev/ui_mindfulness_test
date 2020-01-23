#include "src/ui_mindfulness.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UiMindfulness w;
    w.showMaximized();
    return a.exec();
}
