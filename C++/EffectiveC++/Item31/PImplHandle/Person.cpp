
#include "Person.h"
#include "PersonImpl.h"

Person::Person(const std::string &name, const Date &birthday, const Address &address)
        :   person_impl_(std::make_shared<PersonImpl>(name, birthday, address)) {}

std::string Person::GetName() {
    return person_impl_->GetName();
}
std::string Person::GetBirthday() {
    return person_impl_->GetBirthday();
}
std::string Person::GetAddress() {
    return person_impl_->GetAddress();
}