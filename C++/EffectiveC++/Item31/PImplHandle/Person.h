#ifndef EC16D4B7_47A9_4CA9_B02D_E8A7D27BED99
#define EC16D4B7_47A9_4CA9_B02D_E8A7D27BED99

#include <memory>
#include <string>

class PersonImpl;
class Date;
class Address;

class Person {
public:
    Person(const std::string &name, const Date &birthday, const Address &address);
    std::string GetName();
    std::string GetBirthday();
    std::string GetAddress();

private:
    std::shared_ptr<PersonImpl> person_impl_;
};

#endif /* EC16D4B7_47A9_4CA9_B02D_E8A7D27BED99 */
