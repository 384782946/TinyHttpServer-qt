#include "TrayMenu.hpp"

#include <QAction>
#include <QIcon>
#include <QMenu>

TrayMenu::TrayMenu(QObject *parent)
    :QSystemTrayIcon(parent)
{
    // 初始化菜单项
    initMenu();
    // 设置托盘图标和提示信息
    this->setToolTip(tr("Tiny Http Server"));
    this->setIcon(QIcon(":/icon/tray.ico"));
    // 设置上下文菜单
    this->setContextMenu(_menu);
    // 点击托盘执行的事件
    connect(this,&TrayMenu::messageClicked,_menu,&QMenu::show);
    //显示托盘
    this->show();
    //托盘显示提示信息
    this->showMessage(QString("Tiny Http Server"),QString("Click to operate"));
}

void TrayMenu::initMenu()
{
    // 创建菜单项
    _act_showoption = new QAction(tr("show option"),this);///< 显示选项编辑窗口
    _act_start = new QAction(tr("start server"),this);     ///< 启动服务
    _act_stop = new QAction(tr("stop server"),this);      ///< 停止服务
    _act_restart = new QAction(tr("restart server"),this);   ///< 重启服务
    _act_exit = new QAction(tr("exit"),this);      ///< 退出程序
    // 设置菜单项图标
    _act_showoption->setIcon(QIcon(":/icon/setting.ico"));
    _act_start->setIcon(QIcon(":/icon/start.ico"));
    _act_stop->setIcon(QIcon(":/icon/stop.ico"));
    _act_restart->setIcon(QIcon(":/icon/restart2.ico"));
    _act_exit->setIcon(QIcon(":/icon/exit.ico"));

    // 设置信号和信号连接
    connect(_act_showoption,&QAction::triggered,this,&TrayMenu::showOptionClicked);
    connect(_act_start,&QAction::triggered,this,&TrayMenu::startClicked);
    connect(_act_stop,&QAction::triggered,this,&TrayMenu::stopClicked);
    connect(_act_restart,&QAction::triggered,this,&TrayMenu::restartClicked);
    connect(_act_exit,&QAction::triggered,this,&TrayMenu::deleteLater);

    // 创建菜单
    _menu = new QMenu;
    _menu->addAction(_act_start);
    _menu->addAction(_act_stop);
    _menu->addAction(_act_restart);
    _menu->addSeparator();
    _menu->addAction(_act_showoption);
    _menu->addAction(_act_exit);
    // 设置基本宽高
    //_menu->setBaseSize(128,32);
    _menu->setStyleSheet("QMenu::item{ height:32px;}");
    // 设置不显示
    _menu->setVisible(false);
}

