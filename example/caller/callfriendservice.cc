#include <iostream>
#include "mprpcapplication.h"
#include "friend.pb.h"
#include "mprpcchannel.h"

int main(int argc, char **argv)
{
    // 整个程序启动以后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法GetFrindsList
    fixbug::FriendServiceRpc_Stub stub(new MprpcChannel()); // protobuf service生成的两个类，其中stub类作为是消费者（rpc调用者）
    // rpc方法的请求参数
    fixbug::GetFriendsListRequest request; // 登录请求
    request.set_userid(1);
    // rpc方法的响应
    fixbug::GetFriendsListResponse response;
    MprpcController controller;
    // 发起rpc方法的调用 ， 这是同步的rpc调用过程  MprpcChannel::callmethod，数据序列化然后发送，等待远程的rpc给我响应这个执行的方法结果
    stub.GetFrindsList(&controller, &request, &response, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送

    // 程序跑到这，说明一次rpc调用完成，读调用的结果
    if (0 == response.result().errcode())
    {
        std::cout << "rpc GetFrindsList response success:" << std::endl;
        int size = response.friends_size(); // 获取好友的数量
        for (int i = 0; i < size; ++i)      // 遍历，打印
        {
            std::cout << "index:" << (i + 1) << " name:" << response.friends(i) << std::endl;
        }
    }
    else
    {
        std::cout << "rpc GetFrindsList response error : " << response.result().errmsg() << std::endl;
    }
    // 一次rpc调用完成，读调用的结果
    if (controller.Failed()) // RPC调用过程中出现错误了
    {
        std::cout << controller.ErrorText() << std::endl;
    }
    else // RPC调用成功
    {
        if (0 == response.result().errcode()) // 响应成功
        {
            std::cout << "rpc GetFriendsList response success!" << std::endl;
            int size = response.friends_size(); // 获取好友的个数
            for (int i = 0; i < size; ++i)      // 变量，打印
            {
                std::cout << "index:" << (i + 1) << " name:" << response.friends(i) << std::endl;
            }
        }
        else // 响应失败
        {
            std::cout << "rpc GetFriendsList response error : " << response.result().errmsg() << std::endl;
        }
    }
    return 0;
}