#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <string>
#include <functional>
#include <iostream>
#include <google/protobuf/service.h> // 添加这一行


// 框架提供的专门发布rpc服务的网络对象类
class RpcProvider
{
public:
    // 这里是框架提供给外部使用的，可以发布rpc方法的函数接口
    // void NotifyService(google::protobuf::Service *service);
    // 框架是可以接收各种RPC服务的，不能依赖具体的某一个业务。
    // 基类指针指向子对象
    // 发布RPC服务的方法
    void NotifyService(google::protobuf::Service *service);
    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();

private:
    // 组合EventLoop
    muduo::net::EventLoop m_eventLoop;

    // 新的socket连接回调
    void OnConnection(const muduo::net::TcpConnectionPtr &);
    // 如果muduo库发现有读写，就做 已经建立连接用户的读写事件回调
    void OnMessage(const muduo::net::TcpConnectionPtr &, muduo::net::Buffer *, muduo::Timestamp);
};
