#ifndef F74EE99E_0A31_40BE_AB98_3DED6C7D2CF5
#define F74EE99E_0A31_40BE_AB98_3DED6C7D2CF5

#include <atomic>
#include "Lock.h"

class SpinLock: public Lock {
public:
    virtual void lock() override {
        while (locked.test_and_set()) {}
    }

    virtual void unlock() override { locked.clear(); }

private:
    std::atomic_flag locked = ATOMIC_FLAG_INIT;
};

#endif /* F74EE99E_0A31_40BE_AB98_3DED6C7D2CF5 */
