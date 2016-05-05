#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

extern "C"{
#include "mongoose.h"
}

#include <thread>
#include <atomic>

// 这里为了将来不使用Qt的时候比较方便,所以没有使用QT的定时器来做轮询
// 而是采用了std的线程.

class WebServer
{
    WebServer();
public:
    ~WebServer();
    // 获取单例对象
    static WebServer* getInstance();

    // 启动服务器
    void start();
    // 停止服务器
    void stop();
    // 重启服务器
    void reStart();
    // 设置服务器Web根目录
    void setDocumentRoot(const char* rootpath);
    // 获取当前的根目录
    const char* getDocumentRoot()const;
    // 设置使用的端口号
    void setPort(unsigned short port);
    // 获取当前的端口号
    unsigned short getPort()const;
    // 设置是否开启列出文件选项
    void setEnableDirectoryListing(bool enable=true);
    // 当前是否开启列出文件选项
    bool isEnableDirectoryListing()const;

private:
    // 刷新服务器参数
    void updateServerParameters();
    // 服务器事件轮询
    void doServerPoll();

private:
    // Mongoose事件处理函数
    static void ev_handler(struct mg_connection* nc,int ev,void* p);
    // Mongoose服务HTTP选项
    static struct mg_serve_http_opts   opts;
    // 单例对象指针
    static WebServer*       instanceServe;

    unsigned short          _port;  ///< 使用的端口号
    char*                   _root;  ///< Web根目录
    bool                    _dirList;

    struct mg_mgr           _mgr;   ///< Mongoose 事件管理对象
    struct mg_connection*   _pnc;   ///< Mongoose 连接器对象
    std::thread*            _thr;   ///< Mongoose 运行在的线程管理对象
    std::atomic_bool        _thrIsRun;  ///< 线程执行操控
};

#endif // WEBSERVER_HPP
