#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Integer.hpp>
#include <TFunction_ExecutionStatus.hpp>
#include <Standard_OStream.hpp>
class TFunction_Scope;
class TDF_Label;

class TFunction_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TFunction_Iterator();

  Standard_EXPORT TFunction_Iterator(const TDF_Label& Access);

  Standard_EXPORT virtual void Init(const TDF_Label& Access);

  Standard_EXPORT void SetUsageOfExecutionStatus(const bool usage);

  Standard_EXPORT bool GetUsageOfExecutionStatus() const;

  Standard_EXPORT virtual int GetMaxNbThreads() const;

  Standard_EXPORT virtual const NCollection_List<TDF_Label>& Current() const;

  Standard_EXPORT virtual bool More() const;

  Standard_EXPORT virtual void Next();

  Standard_EXPORT TFunction_ExecutionStatus GetStatus(const TDF_Label& func) const;

  Standard_EXPORT void SetStatus(const TDF_Label&                func,
                                 const TFunction_ExecutionStatus status) const;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& OS) const;

private:
  NCollection_List<TDF_Label>  myCurrent;
  bool                         myUsageOfExecutionStatus;
  NCollection_Map<TDF_Label>   myPassedFunctions;
  occ::handle<TFunction_Scope> myScope;
};
