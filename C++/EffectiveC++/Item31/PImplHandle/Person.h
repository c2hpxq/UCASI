#ifndef EC16D4B7_47A9_4CA9_B02D_E8A7D27BED99
#define EC16D4B7_47A9_4CA9_B02D_E8A7D27BED99

#include <memory>
#include <string>

// 仅接口声明使用，不需要这些类的定义
// 在使用接口的client代码自会包含这些类的定义
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
