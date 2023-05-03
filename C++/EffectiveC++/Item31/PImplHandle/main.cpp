#include "Person.h"
#include "Date.h"
#include "Address.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    Date birthday{.date_ = "1993-08-07"};
    Address address{.addr_ = "zhuzong"};
    Person p("pjq", birthday, address);
    cout << "Name: " << p.GetName() << endl
         << "Birthday: " << p.GetBirthday() << endl
         << "Address: " << p.GetAddress() << endl;

    return 0;
}