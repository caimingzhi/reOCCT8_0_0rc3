#pragma once

#include <functional>

#include <Standard_HashUtils.hpp>

#define DEFINE_HASHER(HasherName, TheKeyType, HashFunctor, EqualFunctor)                           \
  struct HasherName : protected HashFunctor, EqualFunctor                                          \
  {                                                                                                \
    size_t operator()(const TheKeyType& theKey) const noexcept                                     \
    {                                                                                              \
      return HashFunctor::operator()(theKey);                                                      \
    }                                                                                              \
                                                                                                   \
    bool operator()(const TheKeyType& theK1, const TheKeyType& theK2) const noexcept               \
    {                                                                                              \
      return EqualFunctor::operator()(theK1, theK2);                                               \
    }                                                                                              \
  };

template <class TheKeyType>
struct NCollection_DefaultHasher
{
  size_t operator()(const TheKeyType& theKey) const noexcept
  {
    return HashCode<TheKeyType>(theKey);
  }

  bool operator()(const TheKeyType& theK1, const TheKeyType& theK2) const noexcept
  {
    return IsEqual<TheKeyType>(theK1, theK2);
  }

private:
  template <class T = TheKeyType>
  typename std::enable_if<!std::is_enum<T>::value, size_t>::type HashCode(
    const TheKeyType& theKey) const noexcept
  {
    return std::hash<TheKeyType>{}(theKey);
  }

  template <class T = TheKeyType>
  typename std::enable_if<!std::is_enum<T>::value, bool>::type IsEqual(
    const TheKeyType& theK1,
    const TheKeyType& theK2) const noexcept
  {
    return std::equal_to<TheKeyType>{}(theK1, theK2);
  }

  template <class T = TheKeyType>
  typename std::enable_if<std::is_enum<T>::value, size_t>::type HashCode(
    const TheKeyType& theKey) const noexcept
  {
    return static_cast<size_t>(theKey);
  }

  template <class T = TheKeyType>
  typename std::enable_if<std::is_enum<T>::value, bool>::type IsEqual(
    const TheKeyType& theK1,
    const TheKeyType& theK2) const noexcept
  {
    return theK1 == theK2;
  }
};

#define DEFINE_DEFAULT_HASHER_PURE(TheKeyType)                                                     \
  template <>                                                                                      \
  struct NCollection_DefaultHasher<TheKeyType>                                                     \
  {                                                                                                \
    size_t operator()(const TheKeyType theKey) const noexcept                                      \
    {                                                                                              \
      return static_cast<size_t>(theKey);                                                          \
    }                                                                                              \
                                                                                                   \
    bool operator()(const TheKeyType theK1, const TheKeyType theK2) const noexcept                 \
    {                                                                                              \
      return theK1 == theK2;                                                                       \
    }                                                                                              \
  };

DEFINE_DEFAULT_HASHER_PURE(bool)

DEFINE_DEFAULT_HASHER_PURE(char)

DEFINE_DEFAULT_HASHER_PURE(signed char)

DEFINE_DEFAULT_HASHER_PURE(unsigned char)

DEFINE_DEFAULT_HASHER_PURE(wchar_t)

DEFINE_DEFAULT_HASHER_PURE(char16_t)

DEFINE_DEFAULT_HASHER_PURE(char32_t)

DEFINE_DEFAULT_HASHER_PURE(short)

DEFINE_DEFAULT_HASHER_PURE(int)

DEFINE_DEFAULT_HASHER_PURE(long)

DEFINE_DEFAULT_HASHER_PURE(long long)

DEFINE_DEFAULT_HASHER_PURE(unsigned short)

DEFINE_DEFAULT_HASHER_PURE(unsigned int)

DEFINE_DEFAULT_HASHER_PURE(unsigned long)

DEFINE_DEFAULT_HASHER_PURE(unsigned long long)

template <class TheKeyType>
struct NCollection_DefaultHasher<TheKeyType*>
{
  size_t operator()(const TheKeyType* theKey) const noexcept
  {
    return static_cast<size_t>(reinterpret_cast<std::uintptr_t>(theKey));
  }

  bool operator()(const TheKeyType* theK1, const TheKeyType* theK2) const noexcept
  {
    return theK1 == theK2;
  }
};
