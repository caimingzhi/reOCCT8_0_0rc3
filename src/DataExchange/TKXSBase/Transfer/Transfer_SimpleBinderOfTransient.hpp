#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Transfer_Binder.hpp>

//! An adapted instantiation of SimpleBinder for Transient Result,
//! i.e. ResultType can be computed from the Result itself,
//! instead of being static
class Transfer_SimpleBinderOfTransient : public Transfer_Binder
{

public:
  //! Creates an empty SimpleBinderOfTransient
  //! Returns True if a starting object is bound with SEVERAL
  //! results : Here, returns always False
  //! See Binder itself
  Standard_EXPORT Transfer_SimpleBinderOfTransient();

  //! Returns the Effective (Dynamic) Type of the Result
  //! (Standard_Transient if no Result is defined)
  Standard_EXPORT occ::handle<Standard_Type> ResultType() const override;

  //! Returns the Effective Name of (Dynamic) Type of the Result
  //! (void) if no result is defined
  Standard_EXPORT const char* ResultTypeName() const override;

  //! Defines the Result
  Standard_EXPORT void SetResult(const occ::handle<Standard_Transient>& res);

  //! Returns the defined Result, if there is one
  Standard_EXPORT const occ::handle<Standard_Transient>& Result() const;

  //! Returns a transient result according to its type (IsKind)
  //! i.e. the result itself if IsKind(atype), else searches in
  //! NextResult, until first found, then returns True
  //! If not found, returns False (res is NOT touched)
  //!
  //! This syntactic form avoids to do DownCast : if a result is
  //! found with the good type, it is loaded in <res> and can be
  //! immediately used, well initialised
  Standard_EXPORT static bool GetTypedResult(const occ::handle<Transfer_Binder>& bnd,
                                             const occ::handle<Standard_Type>&   atype,
                                             occ::handle<Standard_Transient>&    res);

  DEFINE_STANDARD_RTTIEXT(Transfer_SimpleBinderOfTransient, Transfer_Binder)

private:
  occ::handle<Standard_Transient> theres;
};
