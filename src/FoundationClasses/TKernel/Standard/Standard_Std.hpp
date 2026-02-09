#pragma once

#include <type_traits>

namespace opencascade
{

  namespace std
  {

    using namespace ::std;

  }

  template <class T1, class T2, class Dummy = void>
  struct is_base_but_not_same : opencascade::std::is_base_of<T1, T2>
  {
  };

  template <class T1, class T2>
  struct is_base_but_not_same<
    T1,
    T2,
    typename opencascade::std::enable_if<opencascade::std::is_same<T1, T2>::value>::type>
      : opencascade::std::false_type
  {
  };

  template <typename TheInteger>
  struct is_integer
      : std::integral_constant<bool,
                               opencascade::std::is_integral<TheInteger>::value
                                 && !opencascade::std::is_same<TheInteger, bool>::value>
  {
  };

  template <typename TheType>
  struct disable_deduction
  {
    typedef TheType type;
  };

} // namespace opencascade
