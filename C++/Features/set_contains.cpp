#include <set>
#include <iostream>

using namespace std;

int main() {
    set<int> s{1, 2, 3};

    // g++ set_contains.cpp -std=c++2a
    if (s.contains(1)) {
        cout << "1 in set." << endl;
    }

    return 0;
}