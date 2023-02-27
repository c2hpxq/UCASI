#include "my_spinlock.h"
#include <thread>
#include <vector>
#include <cassert>
#include <chrono>
#include <iostream>

void add_to_counter(int &cnt, int amount, Lock &lock) {
    for (int i = 0; i < amount; ++i) {
        ScopedLock s(lock);

        cnt++;
    }
}

int main() {

    SpinLock spinlock;

    // SpinLock cant_copy_construct = s;

    // SpinLock cant_copy_assign;
    // cant_copy_assign = s;

    int cnt = 0;
    int n_thread = 4;
    int amount = 10000000;

    using namespace std::chrono;
    auto start_time = system_clock::now();

    std::vector<std::thread> vec_ths;
    for (int i = 0; i < n_thread; i++) {
        vec_ths.push_back(std::thread(add_to_counter, std::ref(cnt), amount, std::ref(spinlock)));
    }

    for (auto &th: vec_ths) { th.join(); }

    // assert(cnt == n_thread * amount);

    auto end_time = system_clock::now();

    auto dur = std::chrono::duration_cast<milliseconds>(end_time - start_time);
    std::cout << "Res = " << cnt << std::endl;
    std::cout << "Takes " << dur.count() << "ms." << std::endl;

    return 0;
    
}