#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <NCollection_DataMap.hpp>
#include <TDF_Attribute.hpp>
#include <NCollection_Map.hpp>
class TDF_DataSet;
class TDF_RelocationTable;
class TDF_IDFilter;
class TDF_Label;

//! This class provides services to build, copy or
//! paste a set of information.
//!
//! Copy methods:
//! -------------
//!
//! * Copy(aSourceDataSet, aTargetLabel,
//! aRelocationTable) copies a source DataSet under
//! its target place (see below: IMPORTANT NOTICE 1).
//!
//! * Copy(aSourceDataSet, anTargetLabel,
//! aRelocationTable, aFilter) does the same job as
//! the previous method. But <aFilter> gives a list of
//! IDs for which a target attribute prevails over a
//! source one. In this special case, the source
//! attribute will be copied only if there will be no
//! target attribute.
//!
//! IMPORTANT NOTICE : Label pre-binding
//! ------------------
//!
//! For it is possible to copy root labels in another
//! place in the same Data or in a different one with
//! other tags, it is necessary to inform the Copy
//! algorithm about the target place. To do so:
//!
//! * first get or create new target root labels;
//!
//! * then bind them with the source root labels using
//! the relocation table method:
//! SetRelocation(aSourceLabel, aTargetLabel);
//!
//! * finally call Copy(...) with the relocation table
//! previously set. In this way, this method will take
//! these relocations in account.
class TDF_CopyTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Copy <aSourceDataSet> with using and updating
  //! <aRelocationTable>. This method ignores target
  //! attributes privilege over source ones.
  Standard_EXPORT static void Copy(const occ::handle<TDF_DataSet>&         aSourceDataSet,
                                   const occ::handle<TDF_RelocationTable>& aRelocationTable);

  //! Copy <aSourceDataSet> using and updating
  //! <aRelocationTable>. Use <aPrivilegeFilter> to give
  //! a list of IDs for which the target attribute
  //! prevails over the source one.
  Standard_EXPORT static void Copy(const occ::handle<TDF_DataSet>&         aSourceDataSet,
                                   const occ::handle<TDF_RelocationTable>& aRelocationTable,
                                   const TDF_IDFilter&                     aPrivilegeFilter);

  //! Copy <aSourceDataSet> using and updating
  //! <aRelocationTable>. Use <aPrivilegeFilter> to give
  //! a list of IDs for which the target attribute
  //! prevails over the source one. If <setSelfContained>
  //! is set to true, every TDF_Reference will be
  //! replaced by the referenced structure
  //! according to <aRefFilter>.
  //!
  //! NB: <aRefFilter> is used only if <setSelfContained>
  //! is true.
  //! Internal root label copy recursive method.
  Standard_EXPORT static void Copy(const occ::handle<TDF_DataSet>&         aSourceDataSet,
                                   const occ::handle<TDF_RelocationTable>& aRelocationTable,
                                   const TDF_IDFilter&                     aPrivilegeFilter,
                                   const TDF_IDFilter&                     aRefFilter,
                                   const bool                              setSelfContained);

private:
  //! Internal root label copy recursive method.
  Standard_EXPORT static void CopyLabels(
    const TDF_Label&                                                             aSLabel,
    TDF_Label&                                                                   aTargetLabel,
    NCollection_DataMap<TDF_Label, TDF_Label>&                                   aLabMap,
    NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>>& aAttMap,
    const NCollection_Map<TDF_Label>&                                            aSrcLabelMap,
    const NCollection_Map<occ::handle<TDF_Attribute>>&                           aSrcAttributeMap);

  //! Internal attribute copy method.
  Standard_EXPORT static void CopyAttributes(
    const TDF_Label&                                                             aSLabel,
    TDF_Label&                                                                   aTargetLabel,
    NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>>& aAttMap,
    const NCollection_Map<occ::handle<TDF_Attribute>>&                           aSrcAttributeMap);
};

