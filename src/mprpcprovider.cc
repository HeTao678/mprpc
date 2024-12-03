#include "mprpcprovider.h"
#include "mprpcapplication.h"
// #include "rpcheader.pb.h"

/*
service_name =>对于 service描述
                        =》对应 service* 记录服务对象
                        多个method_name  =>对应多个method方法对象
*/
void RpcProvider::NotifyService(google::protobuf::Service *service)
{
    // 注册服务对象，实际上会将该服务与RPC框架关联
    // 假设框架需要将服务和客户端的请求进行映射
}
// 启动rpc服务节点，开始提供rpc远程网络调用服务


// 新的socket连接回调（也就是新的连接请求）
void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr &conn)
{
}

/*
在框架内部，RpcProvider和RpcConsumer协商好之间通信用的protobuf数据类型
怎么商量呢？
包含：service_name  method_name   args
对应：16UserService   Login    zhang san123456
我们在框架中定义proto的message类型，进行数据头的序列化和反序列化
service_name method_name args_size(防止粘包的问题)

怎么去区分哪个是service_name, method_name, args
我们把消息头表示出来
header_size(4个字节) + header_str + args_str
前面几个字节是服务名和方法名。
为了防止粘包，我们还要记录参数的字符串的长度
我们统一：一开始读4个字节，数据头的长度，也就是除了方法参数之外的所有数据：服务名字和方法名字
10 "10"
10000 "1000000"
std::string   insert和copy方法
*/

// 已建立连接用户的读写事件回调,如果远程有一个rpc服务的调用请求，那么OnMessage方法就会响应
void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr &conn,
                            muduo::net::Buffer *buffer,
                            muduo::Timestamp)
{
}
