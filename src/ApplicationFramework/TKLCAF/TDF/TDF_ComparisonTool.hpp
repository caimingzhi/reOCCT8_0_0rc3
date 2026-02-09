#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class TDF_DataSet;
class TDF_IDFilter;
class TDF_RelocationTable;
class TDF_Label;

class TDF_ComparisonTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Compare(const occ::handle<TDF_DataSet>&         aSourceDataSet,
                                      const occ::handle<TDF_DataSet>&         aTargetDataSet,
                                      const TDF_IDFilter&                     aFilter,
                                      const occ::handle<TDF_RelocationTable>& aRelocationTable);

  Standard_EXPORT static bool SourceUnbound(
    const occ::handle<TDF_DataSet>&         aRefDataSet,
    const occ::handle<TDF_RelocationTable>& aRelocationTable,
    const TDF_IDFilter&                     aFilter,
    const occ::handle<TDF_DataSet>&         aDiffDataSet,
    const int                               anOption = 2);

  Standard_EXPORT static bool TargetUnbound(
    const occ::handle<TDF_DataSet>&         aRefDataSet,
    const occ::handle<TDF_RelocationTable>& aRelocationTable,
    const TDF_IDFilter&                     aFilter,
    const occ::handle<TDF_DataSet>&         aDiffDataSet,
    const int                               anOption = 2);

  Standard_EXPORT static void Cut(const occ::handle<TDF_DataSet>& aDataSet);

  Standard_EXPORT static bool IsSelfContained(const TDF_Label&                aLabel,
                                              const occ::handle<TDF_DataSet>& aDataSet);

private:
  Standard_EXPORT static void Compare(const TDF_Label&                        aSrcLabel,
                                      const TDF_Label&                        aTrgLabel,
                                      const occ::handle<TDF_DataSet>&         aSourceDataSet,
                                      const occ::handle<TDF_DataSet>&         aTargetDataSet,
                                      const TDF_IDFilter&                     aFilter,
                                      const occ::handle<TDF_RelocationTable>& aRelocationTable);

  Standard_EXPORT static bool Unbound(const occ::handle<TDF_DataSet>&         aRefDataSet,
                                      const occ::handle<TDF_RelocationTable>& aRelocationTable,
                                      const TDF_IDFilter&                     aFilter,
                                      const occ::handle<TDF_DataSet>&         aDiffDataSet,
                                      const int                               anOption,
                                      const bool                              theSource);
};
