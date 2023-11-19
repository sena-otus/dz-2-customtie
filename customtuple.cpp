#include <string>
#include <cassert>
#include <utility>
#include <iostream>

template <typename... Args>
struct Customtuple;

template<typename First, typename... Tail>
struct Customtuple<First, Tail...>
{
  explicit Customtuple(First&& first, Tail&&... tail)
    : m_first(std::forward<First>(first)), m_tail(std::forward<Tail>(tail)...)
  {
  }

  using noref_Customtuple = Customtuple<typename std::remove_reference<First>::type, typename std::remove_reference<Tail>::type...>;
  using ref_Customtuple = Customtuple<First&, Tail&...>;
  friend ref_Customtuple;

  Customtuple&operator=(const noref_Customtuple& other)
  {
    m_first = other.m_first;
    m_tail = other.m_tail;
    return *this;
  }

private:
  First m_first;
  Customtuple<Tail...> m_tail;
};


template <>
struct Customtuple<>
{
};

template<class... Types>
Customtuple<Types...> make_Customtuple(Types... args)
{
  return Customtuple<Types...>(std::forward<Types>(args)...);
}


auto getPerson() {
  const std::string name = "Petia";
  const std::string secondName = "Ivanoff";
  const std::size_t age = 23;
  const std::string department = "Sale";
  return make_Customtuple(
    name, secondName, age, department
                         );
}


template<typename... Types>
Customtuple<Types&...> customtie(Types&... args) noexcept
{
   return make_Customtuple<Types&...>(args...);

     // for the next line to complile, explicit from Customtuple ctor must be removed, so what is less evil?
     // return {args...};
}


// NOLINTNEXTLINE(hicpp-named-parameter,readability-named-parameter)
int main(int, char *[]) {
  std::string name;
  std::string secondName;
  std::string department;
  std::size_t age{0};
  customtie(name, secondName, age, department) = getPerson();
  assert(name == "Petia");
  assert(secondName == "Ivanoff");
  assert(age == 23);
  assert(department == "Sale");
  return 0;
}
