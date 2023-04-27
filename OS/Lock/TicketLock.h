#ifndef A8D313BF_66EA_4518_84CA_3A7781B96597
#define A8D313BF_66EA_4518_84CA_3A7781B96597

#include <atomic>
#include "Lock.h"

class TicketLock: public Lock {
public:
    TicketLock(): turn(0), ticket(0) {}

    virtual void lock() override {
        int myturn = ticket++;
        while (turn != myturn) {}
    }

    virtual void unlock() override {
        turn++;
    }

private:
    std::atomic<int> turn;
    std::atomic<int> ticket;
};

#endif /* A8D313BF_66EA_4518_84CA_3A7781B96597 */
