#ifndef D17CE724_B737_4503_8DD4_03F708AE4D89
#define D17CE724_B737_4503_8DD4_03F708AE4D89

class Lock {
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

class ScopedLock {
public:
    ScopedLock(Lock &lock): lock_(lock) {
        lock_.lock();
    }

    virtual ~ScopedLock() {
        lock_.unlock();
    }
private:
    Lock &lock_;
};

#endif /* D17CE724_B737_4503_8DD4_03F708AE4D89 */
