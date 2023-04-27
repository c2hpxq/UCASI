#ifndef D9CEB8DE_D6E3_4EBC_BF54_E1C754EDECFB
#define D9CEB8DE_D6E3_4EBC_BF54_E1C754EDECFB

#include "Lock.h"
#include "SpinLock.h"


class ConcurrentCounter {
public:
    ConcurrentCounter(int init, Lock &lock):
        value_(init),
        lock_(lock)
    {}

    void Increment() {
        ScopedLock sl(lock_);
        value_++;
    }

    void Decrement() {
        ScopedLock sl(lock_);
        value_--;
    }

    int Get() {
        ScopedLock sl(lock_);
        return value_;
    }

private:
    int value_;
    Lock &lock_;
};

#endif /* D9CEB8DE_D6E3_4EBC_BF54_E1C754EDECFB */
