#include <utility>
#include <vector>
#include <iostream>

using namespace std;

struct A {
    int x;
    int y;
};

int main() {
    vector<pair<int, int>> points = { {1, 2}, {3, 4} };

    for (const auto &point: points) {
        const auto & [x, y] = point;
        cout << "(" << x << ", " << y << ")" << endl;
    }

    // warning: structured bindings only available
    // with ‘-std=c++17’ or ‘-std=gnu++17’
    for (const auto & [x, y]: points) {
        cout << "(" << x << ", " << y << ")" << endl;
    }

    A a{.x = 10, .y = 20};
    auto &[x, y] = a;
    cout << x << ", " << y << endl;

    x = 30;
    cout << a.x << ", " << a.y << endl;

    return 0;
}