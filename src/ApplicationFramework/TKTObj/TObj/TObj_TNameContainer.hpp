#pragma once

#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HExtendedString.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TDF_Attribute.hpp>
class TObj_Object;

class TObj_TNameContainer : public TDF_Attribute
{
public:
  Standard_EXPORT TObj_TNameContainer();

  static Standard_EXPORT const Standard_GUID& GetID();

  Standard_EXPORT const Standard_GUID& ID() const override;

public:
  static Standard_EXPORT occ::handle<TObj_TNameContainer> Set(const TDF_Label& theLabel);

public:
  Standard_EXPORT void RecordName(const occ::handle<TCollection_HExtendedString>& theName,
                                  const TDF_Label&                                theLabel);

  Standard_EXPORT void RemoveName(const occ::handle<TCollection_HExtendedString>& theName);

  Standard_EXPORT bool IsRegistered(const occ::handle<TCollection_HExtendedString>& theName) const;

  Standard_EXPORT void Clear();

public:
  Standard_EXPORT void Set(
    const NCollection_DataMap<occ::handle<TCollection_HExtendedString>, TDF_Label>& theElem);

  Standard_EXPORT const NCollection_DataMap<occ::handle<TCollection_HExtendedString>, TDF_Label>&
                        Get() const;

public:
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

private:
  NCollection_DataMap<occ::handle<TCollection_HExtendedString>, TDF_Label> myMap;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_TNameContainer, TDF_Attribute)
};

#ifdef _MSC_VER
  #pragma once
#endif
