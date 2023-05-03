#ifndef D01F0BF6_716A_4D89_9E3B_22C7BB6F8EDD
#define D01F0BF6_716A_4D89_9E3B_22C7BB6F8EDD

#include <string>

#include "Address.h"
#include "Date.h"

class PersonImpl {
public:
    PersonImpl(const std::string &name, const Date &birthday, const Address &address)
        :   name_(name),
            birthday_(birthday),
            address_(address) {}

    std::string GetName() {
        return name_;
    }

    std::string GetBirthday() {
        return birthday_.date_;
    }
    std::string GetAddress() {
        return address_.addr_;
    }

private:
    std::string name_;
    Date birthday_;
    Address address_;
};

#endif /* D01F0BF6_716A_4D89_9E3B_22C7BB6F8EDD */
