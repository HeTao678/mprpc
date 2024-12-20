#pragma once
#include <google/protobuf/service.h>
#include <string>
class MprpcController : public google::protobuf::RpcController
{
public:
    MprpcController();                         // 构造函数
    void Reset();                              // 将 RpcController 的状态重置为初始状态，用于重复使用
    bool Failed() const;                       // 返回一个布尔值，表示调用是否出错。
    std::string ErrorText() const;             // 返回具体的错误描述字符串，方便调试和日志记录
    void SetFailed(const std::string &reason); // 在任何阶段出错(如序列化失败、网络发送失败)时调用.

    // 下面三个都不需要用上
    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure *callback);

private:
    bool m_failed;         // RPC方法执行过程中的状态
    std::string m_errText; // RPC方法执行过程中的错误信息
};