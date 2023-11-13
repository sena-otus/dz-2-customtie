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


    // that works:
template<typename... Args>
std::tuple<Args&...> customtie1(Args&... args) noexcept
{
  return std::tuple<Args&...>(args...);
}


  // that works too:
template<typename... Args>
std::tuple<Args&...> customtie2(Args&... args) noexcept
{
  return {args...};
}

// NOLINTNEXTLINE(hicpp-named-parameter,readability-named-parameter)
int main(int, char *[]) {
  std::string name;
  std::string secondName;
  std::string department;
  std::size_t age{0};
  customtie1(name, secondName, age, department) = getPerson();
  assert(name == "Petia");
  assert(secondName == "Ivanoff");
  assert(age == 23);
  assert(department == "Sale");

  name.clear();
  secondName.clear();
  department.clear();
  age = 0;
  customtie2(name, secondName, age, department) = getPerson();
  assert(name == "Petia");
  assert(secondName == "Ivanoff");
  assert(age == 23);
  assert(department == "Sale");
  return 0;
}
