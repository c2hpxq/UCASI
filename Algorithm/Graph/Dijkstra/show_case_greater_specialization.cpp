#include <functional>
#include <iostream>

using namespace std;

class B;

class A {
    friend int operator>(const A &a, const B &b);
public:
    A(int x): x_(x) {}
private:
    int x_;
};

class B {
    friend int operator>(const A &a, const B &b);
public:
    B(int x): x_(x) {}
private:
    int x_;
};

int operator>(const A &a, const B &b) {
    return a.x_ - b.x_;
}

int main() {
    cout << greater<>()(A(30), B(10)) << endl;

    return 0;
}