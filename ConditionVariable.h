
#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

class ConditionVariable final {
public:
    void wait() noexcept;
    template <typename Function, typename... Args>
    void wait(Function &&func, Args &&...args) noexcept;
    void signal() noexcept;
    void signalAll() noexcept;

private:
    std::mutex              _mutex;
    std::condition_variable _condVar;
};

// DO NOT MANIPULATE ANY SYCHRONIZATION PRIMITIVES INSIDE THE CALLBACK
template <typename Function, typename... Args>
void ConditionVariable::wait(Function &&func, Args &&...args) noexcept {
    std::unique_lock<std::mutex> lock(_mutex);
    _condVar.wait(lock, std::bind(std::forward<Function>(func), std::forward<Args>(args)...));
}
