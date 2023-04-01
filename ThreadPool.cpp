
#include "ThreadPool.h"

NS_IGAME_BEGIN

uint8_t const ThreadPool::CPU_CORE_COUNT   = std::thread::hardware_concurrency();
uint8_t const ThreadPool::MAX_THREAD_COUNT = CPU_CORE_COUNT - 1;

void ThreadPool::start() {
    if (_running) {
        return;
    }

    _running = true;

    for (uint8_t i = 0; i < MAX_THREAD_COUNT; ++i) {
        addThread();
    }
}

void ThreadPool::stop() {
    if (!_running) {
        return;
    }

    _running = false;

    _event.signalAll();

    for (auto &worker : _workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }

    _workers.clear();
}

void ThreadPool::addThread() {
    assert(_workers.size() < MAX_THREAD_COUNT);

    auto workerLoop = [this]() {
        while (_running) {
            Task task = nullptr;

            if (_tasks.try_dequeue(task)) {
                task();
            } else {
                // Double Check
				_event.wait();
            }
        }
    };

    _workers.emplace_back(workerLoop);
}

NS_IGAME_END
