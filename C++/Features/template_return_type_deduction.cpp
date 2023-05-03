#include <iostream>

using namespace std;

template <typename T, typename U>
auto my_min(const T& a, const U& b) {
    return a < b ? a : b;
}

int main() {
    cout << my_min(4, 3.2) << endl;

    return 0;
}