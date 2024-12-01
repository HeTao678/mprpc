#include <iostream>
#include "test.pb.h"
using namespace fixbug;

int main()
{
    LoginRequest req;
    req.set_name("hetao");
    req.set_pwd("123456");
    // 序列化
    std::string send_str;
    if (req.SerializePartialToString(&send_str))
    {
        std::cout << send_str << std::endl;
    }
    // 反序列化，从send_str里读出来，放进一个LoginRequest req2；
    LoginRequest req2;
    if (req2.ParseFromString(send_str))
    {
        std::cout << req2.name() << std::endl;
        std::cout << req2.pwd() << std::endl;
    }
    std::cout << "LoginResponse:" << std::endl;

    LoginResponse resp;
    resp.set_success(true);
    ResultCode *rc = resp.mutable_result();
    rc->set_errcode(0);
    rc->set_errmsg("999");
    std::string send_resp;
    if (resp.SerializePartialToString(&send_resp))
    {
        std::cout << send_resp << std::endl;
    }

    LoginResponse resp2;
    if (resp2.ParsePartialFromString(send_resp))
    {
        std::cout << resp2.mutable_result() << std::endl;
        std::cout << resp2.success() << std::endl;
    }

    std::cout << "GetFriendListsRespons:" << std::endl;

    GetFriendListsResponse rsp;
    ResultCode *rc2 = rsp.mutable_result();
    rc2->set_errcode(0);
    User *user1 = rsp.add_friend_list();
    user1->set_name("zhang san");
    user1->set_age(20);
    user1->set_sex(User::MAN);

    User *user2 = rsp.add_friend_list();
    user2->set_name("li si");
    user2->set_age(22);
    user2->set_sex(User::MAN);
    std::string send_str2;
    if (rsp.SerializePartialToString(&send_str2))
    {
        std::cout << send_str2 << std::endl;
    }
    // 反序列化回 GetFriendListsResponse 对象
    GetFriendListsResponse rsp2;
    if (rsp2.ParseFromString(send_str2))
    {
        std::cout << "Deserialized result code: " << rsp2.result().errmsg() << std::endl;
        std::cout << "Number of friends: " << rsp2.friend_list_size() << std::endl;

        // 打印好友列表信息
        for (int i = 0; i < rsp2.friend_list_size(); ++i)
        {
            const User &friend_info = rsp2.friend_list(i);
            std::cout << "Friend " << i + 1 << ": "
                      << "Name: " << friend_info.name() << ", "
                      << "Age: " << friend_info.age() << ", "
                      << "Sex: " << (friend_info.sex() == User::MAN ? "Man" : "Woman")
                      << std::endl;
        }
    }
    return 0;
}