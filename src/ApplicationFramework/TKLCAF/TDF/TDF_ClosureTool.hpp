#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <TDF_Attribute.hpp>
class TDF_DataSet;
class TDF_IDFilter;
class TDF_ClosureMode;
class TDF_Label;

class TDF_ClosureTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Closure(const occ::handle<TDF_DataSet>& aDataSet);

  Standard_EXPORT static void Closure(const occ::handle<TDF_DataSet>& aDataSet,
                                      const TDF_IDFilter&             aFilter,
                                      const TDF_ClosureMode&          aMode);

  Standard_EXPORT static void Closure(const TDF_Label&                             aLabel,
                                      NCollection_Map<TDF_Label>&                  aLabMap,
                                      NCollection_Map<occ::handle<TDF_Attribute>>& anAttMap,
                                      const TDF_IDFilter&                          aFilter,
                                      const TDF_ClosureMode&                       aMode);

private:
  Standard_EXPORT static void LabelAttributes(const TDF_Label&                             aLabel,
                                              NCollection_Map<TDF_Label>&                  aLabMap,
                                              NCollection_Map<occ::handle<TDF_Attribute>>& anAttMap,
                                              const TDF_IDFilter&                          aFilter,
                                              const TDF_ClosureMode&                       aMode);
};
