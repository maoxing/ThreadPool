
#pragma once

#include "concurrentqueue/concurrentqueue.h"
#include "concurrentqueue/lightweightsemaphore.h"

class Semaphore final {
public:
    Semaphore() noexcept;
    explicit Semaphore(int initialCount) noexcept;

    void wait() noexcept;
    void signal(int count = 1) noexcept;
    void signalAll() noexcept { IGAMEASSERT(false, ""); } // NOLINT(readability-convert-member-functions-to-static)

private:
    moodycamel::details::Semaphore _semaphore;
};