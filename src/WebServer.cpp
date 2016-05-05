#include "WebServer.hpp"


struct mg_serve_http_opts WebServer::opts;
WebServer* WebServer::instanceServe = NULL;


WebServer::WebServer()
    :_thrIsRun(false),_thr(NULL),
      _port(8000),_dirList(true)
{
    _root = strdup(".");
}

WebServer::~WebServer()
{
    this->stop();
}

//=========================================================

WebServer* WebServer::getInstance()
{
    if(instanceServe == NULL){
        instanceServe = new WebServer;
    }
    return instanceServe;
}


//=========================================================

void WebServer::start()
{
    if(!_thrIsRun){
        _thrIsRun = true;
        if(_thr != NULL){
            delete _thr;
        }
        // 设置线程
        _thr = new std::thread([this](){this->doServerPoll();});
        _thr->detach();
    }
}

void WebServer::stop()
{
    if(_thrIsRun){
        _thrIsRun = false;
    }
    sleep(1);   /// 等待结束
}


void WebServer::reStart()
{
    this->stop();
    this->start();
}


//=========================================================

void WebServer::setDocumentRoot(const char *rootpath)
{
    if(_root != NULL){
        free(_root);
    }
    _root = strdup(rootpath);
}

const char *WebServer::getDocumentRoot()const
{
    return _root;
}

void WebServer::setPort(unsigned short port)
{
    _port = port;
}

unsigned short WebServer::getPort() const
{
    return _port;
}

void WebServer::setEnableDirectoryListing(bool enable)
{
    _dirList = enable;
}

bool WebServer::isEnableDirectoryListing() const
{
    return _dirList;
}

//=========================================================

void WebServer::updateServerParameters()
{
    // 1. 初始化Mgr
    mg_mgr_init(&_mgr,NULL);
    // 2. 绑定
    {
        char buf[16];
        sprintf(buf,"%hu",_port);
        _pnc = mg_bind(&_mgr,buf,WebServer::ev_handler);
    }
    // 3. 设置 HTTP 服务器参数
    {
        mg_set_protocol_http_websocket(_pnc);
        // 设置服务器Web根目录
        opts.document_root = _root;
        // 允许通过WebDAV访问 Allow access via webDav
        opts.dav_document_root = ".";
        // 设置开启目录列表
        opts.enable_directory_listing = _dirList?"yes":"no";
    }
}

//=========================================================

void WebServer::doServerPoll()
{
    puts("start======");
    // 先更新参数
    updateServerParameters();
    // 进行轮询
    while(_thrIsRun){
        // 进行轮询,超时等待1000ms
        mg_mgr_poll(&_mgr,1000);
    }
    // 释放资源
    mg_mgr_free(&_mgr);
    puts("stop======");
}

void WebServer::ev_handler(mg_connection *nc, int ev, void *p)
{
    if(ev == MG_EV_HTTP_REQUEST){   // http 请求
        mg_serve_http(nc,(http_message*)p,opts);
    }
}
