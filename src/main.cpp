#include "OptionWidget.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OptionWidget w;
    w.show();

    return a.exec();
}
