#pragma once

#include <TDF_Attribute.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class TDataStd_HDataMapOfStringInteger;
class TDataStd_HDataMapOfStringReal;
class TDataStd_HDataMapOfStringString;
class TDataStd_HDataMapOfStringByte;
class TDataStd_HDataMapOfStringHArray1OfInteger;
class TDataStd_HDataMapOfStringHArray1OfReal;
class TCollection_ExtendedString;

class TDataStd_NamedData : public TDF_Attribute
{
public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_NamedData> Set(const TDF_Label& label);

public:
  Standard_EXPORT TDataStd_NamedData();

  Standard_EXPORT bool HasIntegers() const;

  Standard_EXPORT bool HasInteger(const TCollection_ExtendedString& theName) const;

  Standard_EXPORT int GetInteger(const TCollection_ExtendedString& theName);

  Standard_EXPORT void SetInteger(const TCollection_ExtendedString& theName, const int theInteger);

  Standard_EXPORT const NCollection_DataMap<TCollection_ExtendedString, int>&
                        GetIntegersContainer();

  Standard_EXPORT void ChangeIntegers(
    const NCollection_DataMap<TCollection_ExtendedString, int>& theIntegers);

  Standard_EXPORT bool HasReals() const;

  Standard_EXPORT bool HasReal(const TCollection_ExtendedString& theName) const;

  Standard_EXPORT double GetReal(const TCollection_ExtendedString& theName);

  Standard_EXPORT void SetReal(const TCollection_ExtendedString& theName, const double theReal);

  Standard_EXPORT const NCollection_DataMap<TCollection_ExtendedString, double>&
                        GetRealsContainer();

  Standard_EXPORT void ChangeReals(
    const NCollection_DataMap<TCollection_ExtendedString, double>& theReals);

  Standard_EXPORT bool HasStrings() const;

  Standard_EXPORT bool HasString(const TCollection_ExtendedString& theName) const;

  Standard_EXPORT const TCollection_ExtendedString& GetString(
    const TCollection_ExtendedString& theName);

  Standard_EXPORT void SetString(const TCollection_ExtendedString& theName,
                                 const TCollection_ExtendedString& theString);

  Standard_EXPORT const NCollection_DataMap<TCollection_ExtendedString, TCollection_ExtendedString>&
                        GetStringsContainer();

  Standard_EXPORT void ChangeStrings(
    const NCollection_DataMap<TCollection_ExtendedString, TCollection_ExtendedString>& theStrings);

  Standard_EXPORT bool HasBytes() const;

  Standard_EXPORT bool HasByte(const TCollection_ExtendedString& theName) const;

  Standard_EXPORT uint8_t GetByte(const TCollection_ExtendedString& theName);

  Standard_EXPORT void SetByte(const TCollection_ExtendedString& theName, const uint8_t theByte);

  Standard_EXPORT const NCollection_DataMap<TCollection_ExtendedString, uint8_t>&
                        GetBytesContainer();

  Standard_EXPORT void ChangeBytes(
    const NCollection_DataMap<TCollection_ExtendedString, uint8_t>& theBytes);

  Standard_EXPORT bool HasArraysOfIntegers() const;

  Standard_EXPORT bool HasArrayOfIntegers(const TCollection_ExtendedString& theName) const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<int>>& GetArrayOfIntegers(
    const TCollection_ExtendedString& theName);

  void SetArrayOfIntegers(const TCollection_ExtendedString&            theName,
                          const occ::handle<NCollection_HArray1<int>>& theArrayOfIntegers)
  {
    Backup();
    setArrayOfIntegers(theName, theArrayOfIntegers);
  }

  Standard_EXPORT const NCollection_DataMap<TCollection_ExtendedString,
                                            occ::handle<NCollection_HArray1<int>>>&
                        GetArraysOfIntegersContainer();

  Standard_EXPORT void ChangeArraysOfIntegers(
    const NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<int>>>&
      theArraysOfIntegers);

  Standard_EXPORT bool HasArraysOfReals() const;

  Standard_EXPORT bool HasArrayOfReals(const TCollection_ExtendedString& theName) const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<double>>& GetArrayOfReals(
    const TCollection_ExtendedString& theName);

  void SetArrayOfReals(const TCollection_ExtendedString&               theName,
                       const occ::handle<NCollection_HArray1<double>>& theArrayOfReals)
  {
    Backup();
    setArrayOfReals(theName, theArrayOfReals);
  }

  Standard_EXPORT const NCollection_DataMap<TCollection_ExtendedString,
                                            occ::handle<NCollection_HArray1<double>>>&
                        GetArraysOfRealsContainer();

  Standard_EXPORT void ChangeArraysOfReals(
    const NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<double>>>&
      theArraysOfReals);

  void Clear()
  {
    Backup();
    clear();
  }

public:
  virtual bool HasDeferredData() const { return false; }

  virtual bool LoadDeferredData(bool theToKeepDeferred = false)
  {
    (void)theToKeepDeferred;
    return false;
  }

  virtual bool UnloadDeferredData() { return false; }

public:
  Standard_EXPORT void clear();

  Standard_EXPORT void setInteger(const TCollection_ExtendedString& theName, const int theInteger);

  Standard_EXPORT void setReal(const TCollection_ExtendedString& theName, const double theReal);

  Standard_EXPORT void setString(const TCollection_ExtendedString& theName,
                                 const TCollection_ExtendedString& theString);

  Standard_EXPORT void setByte(const TCollection_ExtendedString& theName, const uint8_t theByte);

  Standard_EXPORT void setArrayOfIntegers(
    const TCollection_ExtendedString&            theName,
    const occ::handle<NCollection_HArray1<int>>& theArrayOfIntegers);

  Standard_EXPORT void setArrayOfReals(
    const TCollection_ExtendedString&               theName,
    const occ::handle<NCollection_HArray1<double>>& theArrayOfReals);

public:
  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_NamedData, TDF_Attribute)

protected:
  occ::handle<TDataStd_HDataMapOfStringInteger>          myIntegers;
  occ::handle<TDataStd_HDataMapOfStringReal>             myReals;
  occ::handle<TDataStd_HDataMapOfStringString>           myStrings;
  occ::handle<TDataStd_HDataMapOfStringByte>             myBytes;
  occ::handle<TDataStd_HDataMapOfStringHArray1OfInteger> myArraysOfIntegers;
  occ::handle<TDataStd_HDataMapOfStringHArray1OfReal>    myArraysOfReals;
};
