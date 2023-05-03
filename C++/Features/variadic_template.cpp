#include <iostream>

using namespace std;

template<typename T>
T Add(T v) {
    return v;
}

template<typename T, typename... Args>
T Add(T first, Args... args) {
    return first + Add(args...);
}

int main() {
    cout << Add(1, 2, 3) << endl;
    cout << Add(4, 5, 6, 7) << endl;

    return 0;
}