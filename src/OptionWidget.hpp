#ifndef OPTIONWIDGET_HPP
#define OPTIONWIDGET_HPP

#include <QWidget>
class TrayMenu;

class QLineEdit;
class QCheckBox;
class QPushButton;

class OptionWidget : public QWidget
{
    Q_OBJECT

public:
    OptionWidget(QWidget *parent = 0);
    ~OptionWidget();

public slots:
    // 重写最小化和正常显示
//    void showMinimized();
//    void showNormal();

protected:
    // 刷新显示数据
    void updateShowData();

    // 拖动对象到窗口部件上，触发dragEnterEvent事件
    void dragEnterEvent(QDragEnterEvent *event);
    // 放下对象，触发dropEvent事件
    void dropEvent(QDropEvent *event);
protected slots:
    // 启动服务
    void startServer();
    // 停止服务
    void stopServer();
    // 重启服务
    void reStartServer();
    // 选择根目录
    void selectRootDir();

private:
    QLineEdit*      _edit_port;     ///< 端口编辑
    QCheckBox*      _cbox_dirlist;  ///< 是否目录列出
    QLineEdit*      _edit_rootdir;  ///< 根目录编辑
    QPushButton*    _btn_start;     ///< 启动服务器按钮
    QPushButton*    _btn_stop;      ///< 停止服务器按钮
    QPushButton*    _btn_restart;   ///< 重启服务器按钮

    TrayMenu*       _tray;          ///< 托盘菜单
    Qt::WindowFlags _winflags;      ///< 窗口形态标识
};

#endif // OPTIONWIDGET_HPP
