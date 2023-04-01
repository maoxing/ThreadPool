
#pragma once

#include "igame.h"
#include <atomic>
#include <cassert>
#include <cstdint>
#include <functional>
#include <future>
#include <thread>
#include "Event.h"
#include "base/std/container/list.h"
#include "concurrentqueue/concurrentqueue.h"

NS_IGAME_BEGIN

class ThreadPool final {
public:
    using Task      = std::function<void()>;
    using TaskQueue = moodycamel::ConcurrentQueue<Task>;

    static uint8_t const CPU_CORE_COUNT;
    static uint8_t const MAX_THREAD_COUNT;

    ThreadPool()                       = default;
    ~ThreadPool()                      = default;
    ThreadPool(ThreadPool const &)     = delete;
    ThreadPool(ThreadPool &&) noexcept = delete;
    ThreadPool &operator=(ThreadPool const &) = delete;
    ThreadPool &operator=(ThreadPool &&) noexcept = delete;

    template <typename Function, typename... Args>
    auto dispatchTask(Function &&func, Args &&...args) -> std::future<decltype(func(std::forward<Args>(args)...))>;
    void start();
    void stop();

private:
    using Event = ConditionVariable;

    void addThread();

    TaskQueue                _tasks{};
    igamestd::list<std::thread> _workers{};
    Event                    _event{};
    std::atomic<bool>        _running{false};
    uint8_t                  _workerCount{MAX_THREAD_COUNT};
};

template <typename Function, typename... Args>
auto ThreadPool::dispatchTask(Function &&func, Args &&...args) -> std::future<decltype(func(std::forward<Args>(args)...))> {
    assert(_running);

    using ReturnType   = decltype(func(std::forward<Args>(args)...));
    auto       task    = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<Function>(func), std::forward<Args>(args)...));
    bool const succeed = _tasks.enqueue([task]() {
        (*task)();
    });
    assert(succeed);
    _event.signal();
    return task->get_future();
}

NS_IGAME_END
