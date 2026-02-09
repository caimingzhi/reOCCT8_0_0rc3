#pragma once

#include <NCollection_List.hpp>
#include <TDF_Attribute.hpp>

class TCollection_AsciiString;

#define DEFINE_DERIVED_ATTRIBUTE(Class, Base)                                                      \
  DEFINE_STANDARD_RTTIEXT(Class, Base);                                                            \
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

#define IMPLEMENT_DERIVED_ATTRIBUTE(Class, Base)                                                   \
  IMPLEMENT_STANDARD_RTTIEXT(Class, Base)                                                          \
  static occ::handle<TDF_Attribute> TDF_DERIVED_New##Class()                                       \
  {                                                                                                \
    return new Class();                                                                            \
  }                                                                                                \
  static TDF_DerivedAttribute::NewDerived TDF_DERIVED_##Class(                                     \
    TDF_DerivedAttribute::Register(TDF_DERIVED_New##Class));                                       \
  occ::handle<TDF_Attribute> Class::NewEmpty() const                                               \
  {                                                                                                \
    return TDF_DERIVED_##Class();                                                                  \
  }

#define IMPLEMENT_DERIVED_ATTRIBUTE_WITH_TYPE(Class, Base, NameSpace, TypeName)                    \
  IMPLEMENT_STANDARD_RTTIEXT(Class, Base)                                                          \
  static occ::handle<TDF_Attribute> TDF_DERIVED_New##Class()                                       \
  {                                                                                                \
    return new Class();                                                                            \
  }                                                                                                \
  static TDF_DerivedAttribute::NewDerived TDF_DERIVED_##Class(                                     \
    TDF_DerivedAttribute::Register(TDF_DERIVED_New##Class, NameSpace, TypeName));                  \
  occ::handle<TDF_Attribute> Class::NewEmpty() const                                               \
  {                                                                                                \
    return TDF_DERIVED_##Class();                                                                  \
  }

class TDF_DerivedAttribute
{
public:
  typedef occ::handle<TDF_Attribute> (*NewDerived)();

  Standard_EXPORT static NewDerived Register(NewDerived  theNewAttributeFunction,
                                             const char* theNameSpace = nullptr,
                                             const char* theTypeName  = nullptr);

  Standard_EXPORT static occ::handle<TDF_Attribute> Attribute(const char* theType);

  Standard_EXPORT static const TCollection_AsciiString& TypeName(const char* theType);

  Standard_EXPORT static void Attributes(NCollection_List<occ::handle<TDF_Attribute>>& theList);
};
