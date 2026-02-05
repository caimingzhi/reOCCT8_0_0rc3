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

//! Iterator of the graph of functions
class TFunction_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! An empty constructor.
  Standard_EXPORT TFunction_Iterator();

  //! A constructor.
  //! Initializes the iterator.
  Standard_EXPORT TFunction_Iterator(const TDF_Label& Access);

  //! Initializes the Iterator.
  Standard_EXPORT virtual void Init(const TDF_Label& Access);

  //! Defines the mode of iteration - usage or not of the execution status.
  //! If the iterator takes into account the execution status,
  //! the method ::Current() returns only "not executed" functions
  //! while their status is not changed.
  //! If the iterator ignores the execution status,
  //! the method ::Current() returns the functions
  //! following their dependencies and ignoring the execution status.
  Standard_EXPORT void SetUsageOfExecutionStatus(const bool usage);

  //! Returns usage of execution status by the iterator.
  Standard_EXPORT bool GetUsageOfExecutionStatus() const;

  //! Analyses the graph of dependencies and returns
  //! maximum number of threads may be used to calculate the model.
  Standard_EXPORT virtual int GetMaxNbThreads() const;

  //! Returns the current list of functions.
  //! If the iterator uses the execution status,
  //! the returned list contains only the functions
  //! with "not executed" status.
  Standard_EXPORT virtual const NCollection_List<TDF_Label>& Current() const;

  //! Returns false if the graph of functions is fully iterated.
  Standard_EXPORT virtual bool More() const;

  //! Switches the iterator to the next list of current functions.
  Standard_EXPORT virtual void Next();

  //! A help-function aimed to help the user to check the status of retrurned function.
  //! It calls TFunction_GraphNode::GetStatus() inside.
  Standard_EXPORT TFunction_ExecutionStatus GetStatus(const TDF_Label& func) const;

  //! A help-function aimed to help the user to change the execution status of a function.
  //! It calls TFunction_GraphNode::SetStatus() inside.
  Standard_EXPORT void SetStatus(const TDF_Label&                func,
                                 const TFunction_ExecutionStatus status) const;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& OS) const;

private:
  NCollection_List<TDF_Label>  myCurrent;
  bool                         myUsageOfExecutionStatus;
  NCollection_Map<TDF_Label>   myPassedFunctions;
  occ::handle<TFunction_Scope> myScope;
};
