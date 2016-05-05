#ifndef TRAYMENU_HPP
#define TRAYMENU_HPP


#include <QSystemTrayIcon>

class QAction;
class QMenu;

// 托盘菜单
class TrayMenu
        :public QSystemTrayIcon
{
    Q_OBJECT
public:
    TrayMenu(QObject* parent = 0);
    // 初始化菜单项
    void initMenu();
signals:
    // 显示选项信号
    void showOptionClicked();
    // 启动服务信息
    void startClicked();
    // 停止服务信号
    void stopClicked();
    // 重启服务信号
    void restartClicked();

protected:
    QMenu*   _menu;          ///< 托盘右键菜单
    QAction* _act_showoption;///< 显示选项编辑窗口
    QAction* _act_start;     ///< 启动服务
    QAction* _act_stop;      ///< 停止服务
    QAction* _act_restart;   ///< 重启服务
    QAction* _act_exit;      ///< 退出程序
};

#endif // TRAYMENU_HPP
