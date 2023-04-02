
#include "ConditionVariable.h"

NS_IGAME_BEGIN

void ConditionVariable::wait() noexcept {
    std::unique_lock<std::mutex> lock(_mutex);
    _condVar.wait(lock);
}

void ConditionVariable::signal() noexcept {
    std::lock_guard<std::mutex> lock(_mutex);
    _condVar.notify_one();
}

void ConditionVariable::signalAll() noexcept {
    std::lock_guard<std::mutex> lock(_mutex);
    _condVar.notify_all();
}

NS_IGAME_END
