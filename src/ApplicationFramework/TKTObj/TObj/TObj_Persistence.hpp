#pragma once

#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HExtendedString.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class TObj_Object;

class TDF_Label;

class TObj_Persistence
{
public:
  static Standard_EXPORT occ::handle<TObj_Object> CreateNewObject(const char*      theType,
                                                                  const TDF_Label& theLabel);

  static Standard_EXPORT void DumpTypes(Standard_OStream& theOs);

protected:
  Standard_EXPORT TObj_Persistence(const char* theType);

  virtual Standard_EXPORT ~TObj_Persistence();

  virtual Standard_EXPORT occ::handle<TObj_Object> New(const TDF_Label& theLabel) const = 0;

  static Standard_EXPORT NCollection_DataMap<TCollection_AsciiString, void*>& getMapOfTypes();

private:
  const char* myType;
};

#ifdef SOLARIS

  #define _TOBJOCAF_PERSISTENCE_ACCESS_ public:
#else
  #define _TOBJOCAF_PERSISTENCE_ACCESS_
#endif
#define DECLARE_TOBJOCAF_PERSISTENCE(name, ancestor)                                               \
  name(const TObj_Persistence* p, const TDF_Label& aLabel)                                         \
      : ancestor(p, aLabel)                                                                        \
  {                                                                                                \
    initFields();                                                                                  \
  }                                                                                                \
                                                                                                   \
  _TOBJOCAF_PERSISTENCE_ACCESS_                                                                    \
  class Persistence_ : public TObj_Persistence                                                     \
  {                                                                                                \
                                                                                                   \
  public:                                                                                          \
    Persistence_()                                                                                 \
        : TObj_Persistence(#name)                                                                  \
    {                                                                                              \
    }                                                                                              \
    virtual occ::handle<TObj_Object> New(const TDF_Label& aLabel) const;                           \
  };                                                                                               \
  friend class Persistence_;                                                                       \
  static Persistence_ myPersistence_;

#define IMPLEMENT_TOBJOCAF_PERSISTENCE(name)                                                       \
  name::Persistence_       name::myPersistence_;                                                   \
  occ::handle<TObj_Object> name::Persistence_::New(const TDF_Label& aLabel) const                  \
  {                                                                                                \
    return new name((const TObj_Persistence*)0, aLabel);                                           \
  }

#ifdef _MSC_VER
  #pragma once
#endif
