
#include "Semaphore.h"

NS_IGAME_BEGIN

Semaphore::Semaphore() noexcept
: _semaphore(0) {
}

Semaphore::Semaphore(int initialCount) noexcept
: _semaphore(initialCount) {
}

void Semaphore::wait() noexcept {
    _semaphore.wait();
}

void Semaphore::signal(int count) noexcept {
    _semaphore.signal(count);
}

NS_IGAME_END
