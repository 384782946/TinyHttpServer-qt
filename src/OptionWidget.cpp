#include "OptionWidget.hpp"

#include "WebServer.hpp"

#include "TrayMenu.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QIntValidator>
#include <QGridLayout>

#include <QFileDialog>
#include <QDir>

#include <QDebug>

OptionWidget::OptionWidget(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口布局
    {
        QString btnstyle("QPushButton{"
                            "height: 32px;"
                            "border-radius: 4px;"
                            "border: 1px solid rgb(89, 153, 48);"
                            "background:DimGray;"
                            "color: white;"
                         "}");
        QString editstyle("QLineEdit{"
                              "height: 32px;"
                              "border-radius: 4px;"
                              "border: 1px solid rgb(89, 153, 48);"
                              "background:DimGray;"
                              "color: white;"
                          "}");
        this->setStyleSheet("QWidget{"
                            "border-radius: 4px;"
                            "background:RoyalBlue;"
                            "color: white;"
                            "}");
        // 端口编辑框
        QLabel*     _lab_port = new QLabel(tr("port:"));
        _edit_port = new QLineEdit;
        _edit_port->setValidator(new QIntValidator(80,65535));
        _edit_port->setStyleSheet(editstyle);
        // 是否允许目录列表
        _cbox_dirlist = new QCheckBox(tr("enable directory listing?"));
        // 根目录文件夹
        QLabel*    _lab_rootdir = new QLabel(tr("root:"));
        _edit_rootdir = new QLineEdit;
        QPushButton* _btn_rootdir = new QPushButton(tr("select dir"));
        _edit_rootdir->setStyleSheet(editstyle);
        _btn_rootdir->setStyleSheet(btnstyle);

        this->updateShowData();

        // 启动服务,停止服务,重启服务
        _btn_start = new QPushButton(tr("start"));
        _btn_stop = new QPushButton(tr("stop"));
        _btn_restart = new QPushButton(tr("restart"));

        _btn_start->setIcon(QIcon(":/icon/start.ico"));
        _btn_stop->setIcon(QIcon(":/icon/stop.ico"));
        _btn_restart->setIcon(QIcon(":/icon/restart2.ico"));

        _btn_start->setStyleSheet(btnstyle);
        _btn_stop->setStyleSheet(btnstyle);
        _btn_restart->setStyleSheet(btnstyle);

        _btn_stop->setEnabled(false);
        _btn_restart->setEnabled(false);

        QGridLayout* layout = new QGridLayout(this);
        layout->addWidget(_lab_port,0,0,1,1);
        layout->addWidget(_edit_port,0,1,1,1);
        layout->addWidget(_cbox_dirlist,0,2,1,2);

        layout->addWidget(_lab_rootdir,1,0,1,1);
        layout->addWidget(_edit_rootdir,1,1,1,2);
        layout->addWidget(_btn_rootdir,1,3,1,1);

        layout->addWidget(_btn_start,2,1,1,1);
        layout->addWidget(_btn_stop,2,2,1,1);
        layout->addWidget(_btn_restart,2,3,1,1);

        // 连接信号和槽
        connect(_btn_start,&QPushButton::clicked,
                this,&OptionWidget::startServer);
        connect(_btn_stop,&QPushButton::clicked,
                this,&OptionWidget::stopServer);
        connect(_btn_restart,&QPushButton::clicked,
                this,&OptionWidget::reStartServer);
        connect(_btn_rootdir,&QPushButton::clicked,
                this,&OptionWidget::selectRootDir);
    }
    // 设置托盘菜单
    {
        _tray = new TrayMenu(this);
        // 连接信号和槽
        connect(_tray,&TrayMenu::startClicked,
                this,&OptionWidget::startServer);
        connect(_tray,&TrayMenu::stopClicked,
                this,&OptionWidget::stopServer);
        connect(_tray,&TrayMenu::restartClicked,
                this,&OptionWidget::reStartServer);

        connect(_tray,&TrayMenu::showOptionClicked,
                this,&OptionWidget::showNormal);

        connect(_tray,&TrayMenu::destroyed,
                [this](){this->stopServer();this->close();});
    }
    // 设置窗口标题图标
    this->setWindowIcon(QIcon(":/icon/tray.ico"));
    // 设置窗口的位置
    // 设置不显示close按钮
    _winflags = this->windowFlags();
    // 必须要 Qt::CustomizeWindowHint 否则无效
    this->setWindowFlags(_winflags & ~Qt::WindowCloseButtonHint &~Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);
    //this->showMinimized();
}

OptionWidget::~OptionWidget()
{
    this->stopServer();
}

void OptionWidget::showMinimized()
{
    QWidget::showMinimized();
//    this->setHidden(true);  // 隐藏
//    _winflags = this->windowFlags();
//    this->setWindowFlags(_winflags | Qt::Tool);
}

void OptionWidget::showNormal()
{
    QWidget::showNormal();
    //this->setHidden(false);
    //this->setWindowFlags(_winflags & ~Qt::Tool);
    //设置Qt::WindowStaysOnTopHint之后，窗口始终置顶
    //this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

void OptionWidget::updateShowData()
{
    WebServer* svr = WebServer::getInstance();

    _edit_port->setText(QString().setNum(svr->getPort()));
    _edit_rootdir->setText(QString(svr->getDocumentRoot()));
    _cbox_dirlist->setChecked(svr->isEnableDirectoryListing());
}

void OptionWidget::startServer()
{
    WebServer* svr = WebServer::getInstance();
    svr->setDocumentRoot(_edit_rootdir->text().toStdString().c_str());
    svr->setPort(_edit_port->text().toUShort());
    svr->setEnableDirectoryListing(_cbox_dirlist->isChecked());
    svr->start();

    _btn_start->setEnabled(false);
    _btn_stop->setEnabled(true);
    _btn_restart->setEnabled(true);
}

void OptionWidget::stopServer()
{
    WebServer* svr = WebServer::getInstance();
    svr->stop();
    _btn_start->setEnabled(true);
    _btn_stop->setEnabled(false);
    _btn_restart->setEnabled(true);
}

void OptionWidget::reStartServer()
{
    WebServer* svr = WebServer::getInstance();
    svr->reStart();
    _btn_start->setEnabled(false);
    _btn_stop->setEnabled(true);
    _btn_restart->setEnabled(true);
}

void OptionWidget::selectRootDir()
{

    QString path = QFileDialog::getExistingDirectory(
                this,
                tr("select webserver root directory"),
                _edit_rootdir->text());
    _edit_rootdir->setText(path);
}
