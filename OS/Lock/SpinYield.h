#ifndef E546612D_EE8B_468C_B6C5_F8D353E92426
#define E546612D_EE8B_468C_B6C5_F8D353E92426

#include <atomic>
#include <thread>
#include "Lock.h"

class SpinYield: public Lock {
public:
    virtual void lock() override {
        while (locked.test_and_set()) {
            std::this_thread::yield();
        }
    }

    virtual void unlock() override { locked.clear(); }

private:
    std::atomic_flag locked = ATOMIC_FLAG_INIT;
};

#endif /* E546612D_EE8B_468C_B6C5_F8D353E92426 */
