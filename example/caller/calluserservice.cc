#include <iostream>
#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"

int main(int argc, char **argv)
{
    // 整个程序启动以后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel()); // protobuf service生成的两个类，其中stub类作为是消费者（rpc调用者）
    // rpc方法的请求参数
    fixbug::LoginRequest request; // 登录请求
    request.set_name("hetao");
    request.set_pwd("123456");
    // rpc方法的响应
    fixbug::LoginResponse response;
    // 发起rpc方法的调用 ， 这是同步的rpc调用过程  MprpcChannel::callmethod，数据序列化然后发送，等待远程的rpc给我响应这个执行的方法结果
    stub.Login(nullptr, &request, &response, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送

    // 程序跑到这，说明一次rpc调用完成，读调用的结果
    if (0 == response.result().errcode())
    {
        std::cout << "rpc login response success:" << response.sucess() << std::endl;
    }
    else
    {
        std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
    }

    // 演示调用远程发布的rpc方法Register
    fixbug::UserServiceRpc_Stub stub2(new MprpcChannel()); // protobuf service生成的两个类，其中stub类作为是消费者（rpc调用者）
    // rpc方法的请求参数
    fixbug::RegisterRequest request2; // 登录请求
    request2.set_id(2000);
    request2.set_name("hetao");
    request2.set_pwd("123456");
    // rpc方法的响应
    fixbug::RegisterResponse response2;
    // 发起rpc方法的调用 ， 这是同步的rpc调用过程  MprpcChannel::callmethod，数据序列化然后发送，等待远程的rpc给我响应这个执行的方法结果
    stub2.Register(nullptr, &request2, &response2, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送

    // 程序跑到这，说明一次rpc调用完成，读调用的结果
    if (0 == response2.result().errcode())
    {
        std::cout << "rpc Register response success:" << response2.sucess() << std::endl;
    }
    else
    {
        std::cout << "rpc Register response error : " << response2.result().errmsg() << std::endl;
    }

    return 0;
}
