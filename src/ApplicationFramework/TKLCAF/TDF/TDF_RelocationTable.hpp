#pragma once

#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <NCollection_DataMap.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Handle.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class TDF_Attribute;

class TDF_RelocationTable : public Standard_Transient
{

public:
  Standard_EXPORT TDF_RelocationTable(const bool selfRelocate = false);

  Standard_EXPORT void SelfRelocate(const bool selfRelocate);

  Standard_EXPORT bool SelfRelocate() const;

  Standard_EXPORT void AfterRelocate(const bool afterRelocate);

  Standard_EXPORT bool AfterRelocate() const;

  Standard_EXPORT void SetRelocation(const TDF_Label& aSourceLabel, const TDF_Label& aTargetLabel);

  Standard_EXPORT bool HasRelocation(const TDF_Label& aSourceLabel, TDF_Label& aTargetLabel) const;

  Standard_EXPORT void SetRelocation(const occ::handle<TDF_Attribute>& aSourceAttribute,
                                     const occ::handle<TDF_Attribute>& aTargetAttribute);

  Standard_EXPORT bool HasRelocation(const occ::handle<TDF_Attribute>& aSourceAttribute,
                                     occ::handle<TDF_Attribute>&       aTargetAttribute) const;

  template <class T>
  bool HasRelocation(const occ::handle<TDF_Attribute>& theSource, occ::handle<T>& theTarget) const
  {
    occ::handle<TDF_Attribute> anAttr = theTarget;
    return HasRelocation(theSource, anAttr) && !(theTarget = occ::down_cast<T>(anAttr)).IsNull();
  }

  Standard_EXPORT void SetTransientRelocation(
    const occ::handle<Standard_Transient>& aSourceTransient,
    const occ::handle<Standard_Transient>& aTargetTransient);

  Standard_EXPORT bool HasTransientRelocation(
    const occ::handle<Standard_Transient>& aSourceTransient,
    occ::handle<Standard_Transient>&       aTargetTransient) const;

  Standard_EXPORT void Clear();

  Standard_EXPORT void TargetLabelMap(NCollection_Map<TDF_Label>& aLabelMap) const;

  Standard_EXPORT void TargetAttributeMap(
    NCollection_Map<occ::handle<TDF_Attribute>>& anAttributeMap) const;

  Standard_EXPORT NCollection_DataMap<TDF_Label, TDF_Label>& LabelTable();

  Standard_EXPORT NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>>&
                  AttributeTable();

  Standard_EXPORT NCollection_IndexedDataMap<occ::handle<Standard_Transient>,
                                             occ::handle<Standard_Transient>>&
                  TransientTable();

  Standard_EXPORT Standard_OStream& Dump(const bool        dumpLabels,
                                         const bool        dumpAttributes,
                                         const bool        dumpTransients,
                                         Standard_OStream& anOS) const;

  DEFINE_STANDARD_RTTIEXT(TDF_RelocationTable, Standard_Transient)

private:
  bool                                                                        mySelfRelocate;
  bool                                                                        myAfterRelocate;
  NCollection_DataMap<TDF_Label, TDF_Label>                                   myLabelTable;
  NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>> myAttributeTable;
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>
    myTransientTable;
};
