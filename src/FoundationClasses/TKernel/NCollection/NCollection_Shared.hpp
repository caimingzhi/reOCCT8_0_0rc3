#pragma once

#include <NCollection_DefineAlloc.hpp>

template <class T,
          typename = typename opencascade::std::enable_if<
            !opencascade::std::is_base_of<Standard_Transient, T>::value>::type>
class NCollection_Shared : public Standard_Transient, public T
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

  NCollection_Shared() = default;

  template <typename T1>
  NCollection_Shared(const T1& arg1)
      : T(arg1)
  {
  }

  template <typename T1>
  NCollection_Shared(T1& arg1)
      : T(arg1)
  {
  }

  template <typename T1, typename T2>
  NCollection_Shared(const T1& arg1, const T2& arg2)
      : T(arg1, arg2)
  {
  }

  template <typename T1, typename T2>
  NCollection_Shared(T1& arg1, const T2& arg2)
      : T(arg1, arg2)
  {
  }

  template <typename T1, typename T2>
  NCollection_Shared(const T1& arg1, T2& arg2)
      : T(arg1, arg2)
  {
  }

  template <typename T1, typename T2>
  NCollection_Shared(T1& arg1, T2& arg2)
      : T(arg1, arg2)
  {
  }
};
