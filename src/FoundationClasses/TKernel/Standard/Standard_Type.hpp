#pragma once

#include <Standard.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

#include <typeinfo>
#include <typeindex>

#ifndef OCCT_CHECK_BASE_CLASS
  #include <type_traits>
  #define OCCT_CHECK_BASE_CLASS(Class, Base)                                                       \
    static_assert(std::is_base_of<Base, Class>::value && !std::is_same<Base, Class>::value,        \
                  "OCCT RTTI definition is incorrect: " #Base " is not base class of " #Class);
#endif

#define STANDARD_TYPE(theType) theType::get_type_descriptor()

#define DEFINE_STANDARD_RTTI_INLINE(Class, Base)                                                   \
public:                                                                                            \
  typedef Base                 base_type;                                                          \
  static constexpr const char* get_type_name()                                                     \
  {                                                                                                \
    OCCT_CHECK_BASE_CLASS(Class, Base);                                                            \
    return #Class;                                                                                 \
  }                                                                                                \
  static const occ::handle<Standard_Type>& get_type_descriptor()                                   \
  {                                                                                                \
    static const occ::handle<Standard_Type> THE_TYPE_INSTANCE =                                    \
      Standard_Type::Register(typeid(Class),                                                       \
                              get_type_name(),                                                     \
                              sizeof(Class),                                                       \
                              Base::get_type_descriptor());                                        \
    return THE_TYPE_INSTANCE;                                                                      \
  }                                                                                                \
  virtual const occ::handle<Standard_Type>& DynamicType() const override                           \
  {                                                                                                \
    return get_type_descriptor();                                                                  \
  }

#define DEFINE_STANDARD_RTTIEXT(Class, Base)                                                       \
public:                                                                                            \
  typedef Base                 base_type;                                                          \
  static constexpr const char* get_type_name()                                                     \
  {                                                                                                \
    OCCT_CHECK_BASE_CLASS(Class, Base);                                                            \
    return #Class;                                                                                 \
  }                                                                                                \
  Standard_EXPORT static const occ::handle<Standard_Type>&  get_type_descriptor();                 \
  Standard_EXPORT virtual const occ::handle<Standard_Type>& DynamicType() const override;

#define IMPLEMENT_STANDARD_RTTIEXT(Class, Base)                                                    \
  OCCT_CHECK_BASE_CLASS(Class, Base)                                                               \
  const occ::handle<Standard_Type>& Class::get_type_descriptor()                                   \
  {                                                                                                \
    static const occ::handle<Standard_Type> THE_TYPE_INSTANCE =                                    \
      Standard_Type::Register(typeid(Class),                                                       \
                              get_type_name(),                                                     \
                              sizeof(Class),                                                       \
                              Class::base_type::get_type_descriptor());                            \
    return THE_TYPE_INSTANCE;                                                                      \
  }                                                                                                \
  const occ::handle<Standard_Type>& Class::DynamicType() const                                     \
  {                                                                                                \
    return STANDARD_TYPE(Class);                                                                   \
  }

class Standard_Type : public Standard_Transient
{
public:
  const char* SystemName() const { return mySystemName; }

  const char* Name() const { return myName; }

  size_t Size() const { return mySize; }

  const occ::handle<Standard_Type>& Parent() const { return myParent; }

  Standard_EXPORT bool SubType(const occ::handle<Standard_Type>& theOther) const;

  Standard_EXPORT bool SubType(const char* theOther) const;

  Standard_EXPORT void Print(Standard_OStream& theStream) const;

  template <class T>
  static const occ::handle<Standard_Type>& Instance()
  {
    return T::get_type_descriptor();
  }

  Standard_EXPORT static Standard_Type* Register(const std::type_info&             theInfo,
                                                 const char*                       theName,
                                                 size_t                            theSize,
                                                 const occ::handle<Standard_Type>& theParent);

  Standard_EXPORT ~Standard_Type() override;

  DEFINE_STANDARD_RTTIEXT(Standard_Type, Standard_Transient)

private:
  Standard_Type(const char*                       theSystemName,
                const char*                       theName,
                size_t                            theSize,
                const occ::handle<Standard_Type>& theParent);

private:
  const char*                mySystemName;
  const char*                myName;
  size_t                     mySize;
  occ::handle<Standard_Type> myParent;
};

inline Standard_OStream& operator<<(Standard_OStream&                 theStream,
                                    const occ::handle<Standard_Type>& theType)
{
  theType->Print(theStream);
  return theStream;
}

namespace occ
{

  template <class T>
  inline bool is_kind(const Standard_Transient* theObject)
  {
    return theObject != nullptr && theObject->IsKind(T::get_type_descriptor());
  }

  template <class T, class TBase>
  inline bool is_kind(const handle<TBase>& theObject)
  {
    return !theObject.IsNull() && theObject->IsKind(T::get_type_descriptor());
  }

  template <class T>
  inline bool is_instance(const Standard_Transient* theObject)
  {
    return theObject != nullptr && theObject->IsInstance(T::get_type_descriptor());
  }

  template <class T, class TBase>
  inline bool is_instance(const handle<TBase>& theObject)
  {
    return !theObject.IsNull() && theObject->IsInstance(T::get_type_descriptor());
  }

  template <class T>
  inline const handle<Standard_Type>& type_of()
  {
    return T::get_type_descriptor();
  }

} // namespace occ
