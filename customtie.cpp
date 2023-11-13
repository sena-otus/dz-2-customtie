#include <string>
#include <tuple>
#include <cassert>

auto getPerson() {
  const std::string name = "Petia";
  const std::string secondName = "Ivanoff";
  const std::size_t age = 23;
  const std::string department = "Sale";
  return std::make_tuple(
    name, secondName, age, department
                         );
}

int main(int, char *[]) {
  std::string name, secondName, department;
  std::size_t age;
  std::tie(name, secondName, age, department) = getPerson();
  assert(name == "Petia");
  assert(secondName == "Ivanoff");
  assert(age == 23);
  assert(department == "Sale");
  return 0;
}
