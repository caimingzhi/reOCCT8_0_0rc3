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

class TDF_CopyTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Copy(const occ::handle<TDF_DataSet>&         aSourceDataSet,
                                   const occ::handle<TDF_RelocationTable>& aRelocationTable);

  Standard_EXPORT static void Copy(const occ::handle<TDF_DataSet>&         aSourceDataSet,
                                   const occ::handle<TDF_RelocationTable>& aRelocationTable,
                                   const TDF_IDFilter&                     aPrivilegeFilter);

  Standard_EXPORT static void Copy(const occ::handle<TDF_DataSet>&         aSourceDataSet,
                                   const occ::handle<TDF_RelocationTable>& aRelocationTable,
                                   const TDF_IDFilter&                     aPrivilegeFilter,
                                   const TDF_IDFilter&                     aRefFilter,
                                   const bool                              setSelfContained);

private:
  Standard_EXPORT static void CopyLabels(
    const TDF_Label&                                                             aSLabel,
    TDF_Label&                                                                   aTargetLabel,
    NCollection_DataMap<TDF_Label, TDF_Label>&                                   aLabMap,
    NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>>& aAttMap,
    const NCollection_Map<TDF_Label>&                                            aSrcLabelMap,
    const NCollection_Map<occ::handle<TDF_Attribute>>&                           aSrcAttributeMap);

  Standard_EXPORT static void CopyAttributes(
    const TDF_Label&                                                             aSLabel,
    TDF_Label&                                                                   aTargetLabel,
    NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>>& aAttMap,
    const NCollection_Map<occ::handle<TDF_Attribute>>&                           aSrcAttributeMap);
};
