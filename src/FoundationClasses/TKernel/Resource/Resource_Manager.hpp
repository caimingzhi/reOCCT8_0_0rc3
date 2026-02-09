#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <NCollection_DataMap.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>

class Resource_Manager : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Resource_Manager, Standard_Transient)
public:
  Standard_EXPORT Resource_Manager(const char* aName, const bool Verbose = false);

  Standard_EXPORT Resource_Manager();

  Standard_EXPORT Resource_Manager(const TCollection_AsciiString& theName,
                                   const TCollection_AsciiString& theDefaultsDirectory,
                                   const TCollection_AsciiString& theUserDefaultsDirectory,
                                   const bool                     theIsVerbose = false);

  Standard_EXPORT bool Save() const;

  Standard_EXPORT bool Find(const char* aResource) const;

  Standard_EXPORT bool Find(const TCollection_AsciiString& theResource,
                            TCollection_AsciiString&       theValue) const;

  Standard_EXPORT virtual int Integer(const char* aResourceName) const;

  Standard_EXPORT virtual double Real(const char* aResourceName) const;

  Standard_EXPORT virtual const char* Value(const char* aResourceName) const;

  Standard_EXPORT virtual const char16_t* ExtValue(const char* aResourceName);

  Standard_EXPORT virtual void SetResource(const char* aResourceName, const int aValue);

  Standard_EXPORT virtual void SetResource(const char* aResourceName, const double aValue);

  Standard_EXPORT virtual void SetResource(const char* aResourceName, const char* aValue);

  Standard_EXPORT virtual void SetResource(const char* aResourceName, const char16_t* aValue);

  Standard_EXPORT static void GetResourcePath(TCollection_AsciiString& aPath,
                                              const char*              aName,
                                              const bool               isUserDefaults);

  Standard_EXPORT NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>& GetMap(
    bool theRefMap = true);

  bool IsInitialized() const { return myInitialized; }

private:
  Standard_EXPORT void Load(
    const TCollection_AsciiString&                                         thePath,
    NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>& aMap);

private:
  TCollection_AsciiString                                                  myName;
  NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>    myRefMap;
  NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>    myUserMap;
  NCollection_DataMap<TCollection_AsciiString, TCollection_ExtendedString> myExtStrMap;
  bool                                                                     myVerbose;
  bool                                                                     myInitialized;
};
