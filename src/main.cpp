#include "OptionWidget.hpp"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator tsor;           //创建翻译器
    tsor.load("zh_hans.qm");    //加载语言包
    a.installTranslator(&tsor); //安装翻译器

    OptionWidget w;
    w.show();

    return a.exec();
}
