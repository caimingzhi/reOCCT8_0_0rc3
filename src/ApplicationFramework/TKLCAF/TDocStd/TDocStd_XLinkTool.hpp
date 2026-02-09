#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class TDF_DataSet;
class TDF_RelocationTable;
class TDF_Label;

class TDocStd_XLinkTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDocStd_XLinkTool();

  Standard_EXPORT void CopyWithLink(const TDF_Label& intarget, const TDF_Label& fromsource);

  Standard_EXPORT void UpdateLink(const TDF_Label& L);

  Standard_EXPORT virtual void Copy(const TDF_Label& intarget, const TDF_Label& fromsource);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT occ::handle<TDF_DataSet> DataSet() const;

  Standard_EXPORT occ::handle<TDF_RelocationTable> RelocationTable() const;

protected:
  bool isDone;

private:
  occ::handle<TDF_DataSet>         myDS;
  occ::handle<TDF_RelocationTable> myRT;
};
