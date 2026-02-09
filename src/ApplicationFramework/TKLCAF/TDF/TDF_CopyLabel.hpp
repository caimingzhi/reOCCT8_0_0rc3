#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <TDF_IDFilter.hpp>
#include <TDF_Attribute.hpp>
#include <NCollection_Map.hpp>
class TDF_RelocationTable;
class TDF_DataSet;

class TDF_CopyLabel
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDF_CopyLabel();

  Standard_EXPORT TDF_CopyLabel(const TDF_Label& aSource, const TDF_Label& aTarget);

  Standard_EXPORT void Load(const TDF_Label& aSource, const TDF_Label& aTarget);

  Standard_EXPORT void UseFilter(const TDF_IDFilter& aFilter);

  Standard_EXPORT static bool ExternalReferences(
    const TDF_Label&                             Lab,
    NCollection_Map<occ::handle<TDF_Attribute>>& aExternals,
    const TDF_IDFilter&                          aFilter);

  Standard_EXPORT static void ExternalReferences(
    const TDF_Label&                             aRefLab,
    const TDF_Label&                             Lab,
    NCollection_Map<occ::handle<TDF_Attribute>>& aExternals,
    const TDF_IDFilter&                          aFilter,
    occ::handle<TDF_DataSet>&                    aDataSet);

  Standard_EXPORT void Perform();

  bool IsDone() const;

  Standard_EXPORT const occ::handle<TDF_RelocationTable>& RelocationTable() const;

private:
  occ::handle<TDF_RelocationTable>            myRT;
  TDF_Label                                   mySL;
  TDF_Label                                   myTL;
  TDF_IDFilter                                myFilter;
  NCollection_Map<occ::handle<TDF_Attribute>> myMapOfExt;
  bool                                        myIsDone;
};

inline bool TDF_CopyLabel::IsDone() const
{
  return myIsDone;
}
