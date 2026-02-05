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

//! This is a relocation dictionary between source
//! and target labels, attributes or any
//! transient(useful for copy or paste actions).
//! Note that one target value may be the
//! relocation value of more than one source object.
//!
//! Common behaviour: it returns true and the found
//! relocation value as target object; false
//! otherwise.
//!
//! Look at SelfRelocate method for more explanation
//! about self relocation behavior of this class.
class TDF_RelocationTable : public Standard_Transient
{

public:
  //! Creates an relocation table. <selfRelocate> says
  //! if a value without explicit relocation is its own
  //! relocation.
  Standard_EXPORT TDF_RelocationTable(const bool selfRelocate = false);

  //! Sets <mySelfRelocate> to <selfRelocate>.
  //!
  //! This flag affects the HasRelocation method
  //! behavior like this:
  //!
  //! <mySelfRelocate> == False:
  //!
  //! If no relocation object is found in the map, a
  //! null object is returned
  //!
  //! <mySelfRelocate> == True:
  //!
  //! If no relocation object is found in the map, the
  //! method assumes the source object is relocation
  //! value; so the source object is returned as target
  //! object.
  Standard_EXPORT void SelfRelocate(const bool selfRelocate);

  //! Returns <mySelfRelocate>.
  Standard_EXPORT bool SelfRelocate() const;

  Standard_EXPORT void AfterRelocate(const bool afterRelocate);

  //! Returns <myAfterRelocate>.
  Standard_EXPORT bool AfterRelocate() const;

  //! Sets the relocation value of <aSourceLabel> to
  //! <aTargetLabel>.
  Standard_EXPORT void SetRelocation(const TDF_Label& aSourceLabel, const TDF_Label& aTargetLabel);

  //! Finds the relocation value of <aSourceLabel>
  //! and returns it into <aTargetLabel>.
  //!
  //! (See above SelfRelocate method for more
  //! explanation about the method behavior)
  Standard_EXPORT bool HasRelocation(const TDF_Label& aSourceLabel, TDF_Label& aTargetLabel) const;

  //! Sets the relocation value of <aSourceAttribute> to
  //! <aTargetAttribute>.
  Standard_EXPORT void SetRelocation(const occ::handle<TDF_Attribute>& aSourceAttribute,
                                     const occ::handle<TDF_Attribute>& aTargetAttribute);

  //! Finds the relocation value of <aSourceAttribute>
  //! and returns it into <aTargetAttribute>.
  //!
  //! (See above SelfRelocate method for more
  //! explanation about the method behavior)
  Standard_EXPORT bool HasRelocation(const occ::handle<TDF_Attribute>& aSourceAttribute,
                                     occ::handle<TDF_Attribute>&       aTargetAttribute) const;

  //! Safe variant for arbitrary type of argument
  template <class T>
  bool HasRelocation(const occ::handle<TDF_Attribute>& theSource, occ::handle<T>& theTarget) const
  {
    occ::handle<TDF_Attribute> anAttr = theTarget;
    return HasRelocation(theSource, anAttr) && !(theTarget = occ::down_cast<T>(anAttr)).IsNull();
  }

  //! Sets the relocation value of <aSourceTransient> to
  //! <aTargetTransient>.
  Standard_EXPORT void SetTransientRelocation(
    const occ::handle<Standard_Transient>& aSourceTransient,
    const occ::handle<Standard_Transient>& aTargetTransient);

  //! Finds the relocation value of <aSourceTransient>
  //! and returns it into <aTargetTransient>.
  //!
  //! (See above SelfRelocate method for more
  //! explanation about the method behavior)
  Standard_EXPORT bool HasTransientRelocation(
    const occ::handle<Standard_Transient>& aSourceTransient,
    occ::handle<Standard_Transient>&       aTargetTransient) const;

  //! Clears the relocation dictionary, but lets the
  //! self relocation flag to its current value.
  Standard_EXPORT void Clear();

  //! Fills <aLabelMap> with target relocation
  //! labels. <aLabelMap> is not cleared before use.
  Standard_EXPORT void TargetLabelMap(NCollection_Map<TDF_Label>& aLabelMap) const;

  //! Fills <anAttributeMap> with target relocation
  //! attributes. <anAttributeMap> is not cleared before
  //! use.
  Standard_EXPORT void TargetAttributeMap(
    NCollection_Map<occ::handle<TDF_Attribute>>& anAttributeMap) const;

  //! Returns <myLabelTable> to be used or updated.
  Standard_EXPORT NCollection_DataMap<TDF_Label, TDF_Label>& LabelTable();

  //! Returns <myAttributeTable> to be used or updated.
  Standard_EXPORT NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>>&
                  AttributeTable();

  //! Returns <myTransientTable> to be used or updated.
  Standard_EXPORT NCollection_IndexedDataMap<occ::handle<Standard_Transient>,
                                             occ::handle<Standard_Transient>>&
                  TransientTable();

  //! Dumps the relocation table.
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
