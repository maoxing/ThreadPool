
#pragma once

#include "ConditionVariable.h"
#include "Semaphore.h"

template <typename T>
class Event final {
public:
    inline void wait() noexcept { _syncObject.wait(); }
    inline void signal() noexcept { _syncObject.signal(); };
    inline void signalAll() noexcept { _syncObject.signalAll(); }

private:
    T _syncObject{};
};

using EventCV  = Event<ConditionVariable>;
using EventSem = Event<Semaphore>;
