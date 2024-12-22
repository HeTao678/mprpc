#pragma once
#include <queue>
#include <thread>
#include <mutex>              //其实就是调用pthread_mutex_t
#include <condition_variable> //其实就是调用pthread_condition_t

// 异步写日志的日志队列
template <typename T>
class LockQueue
{
public:
    // 多个worker线程都会写日志queue
    // 插入数据到队列中（线程安全的生产者方法）
    void Push(const T &data)
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 自动加锁和解锁，获取锁，函数结束自动释放锁
        m_queue.push(data);                        // 入队列
        m_condvariable.notify_one();               // 通知等待的消费者，唤醒一个线程
    }

    // 一个线程读日志queue，写日志文件
    // 从队列中取数据（线程安全的消费者方法）
    T Pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex); // 获取锁，函数结束自动释放锁
        while (m_queue.empty())                     // 如果队列为空，则等待
        {
            // 日志队列为空，线程进入wait状态
            m_condvariable.wait(lock); // 线程挂起，阻塞，释放锁
        }

        T data = m_queue.front(); // 取队列头
        m_queue.pop();            // 出队列，弹出头部数据
        return data;
    }

private:
    std::queue<T> m_queue;                  // 队列
    std::mutex m_mutex;                     // 互斥锁，保护队列
    std::condition_variable m_condvariable; // 条件变量，用于线程同步
};
