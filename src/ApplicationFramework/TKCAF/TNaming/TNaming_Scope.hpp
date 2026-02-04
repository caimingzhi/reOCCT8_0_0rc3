#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
class TDF_Label;
class TopoDS_Shape;
class TNaming_NamedShape;

//! this class manage a scope of labels
//! ===================================
class TNaming_Scope
{
public:
  DEFINE_STANDARD_ALLOC

  //! WithValid = FALSE
  Standard_EXPORT TNaming_Scope();

  //! if <WithValid> the scope is defined by the map. If not
  //! on the whole framework.
  Standard_EXPORT TNaming_Scope(const bool WithValid);

  //! create a scope with a map. WithValid = TRUE.
  Standard_EXPORT TNaming_Scope(NCollection_Map<TDF_Label>& valid);

  Standard_EXPORT bool WithValid() const;

  Standard_EXPORT void WithValid(const bool mode);

  Standard_EXPORT void ClearValid();

  Standard_EXPORT void Valid(const TDF_Label& L);

  Standard_EXPORT void ValidChildren(const TDF_Label& L, const bool withroot = true);

  Standard_EXPORT void Unvalid(const TDF_Label& L);

  Standard_EXPORT void UnvalidChildren(const TDF_Label& L, const bool withroot = true);

  Standard_EXPORT bool IsValid(const TDF_Label& L) const;

  Standard_EXPORT const NCollection_Map<TDF_Label>& GetValid() const;

  Standard_EXPORT NCollection_Map<TDF_Label>& ChangeValid();

  //! Returns the current value of <NS> according to the
  //! Valid Scope.
  Standard_EXPORT TopoDS_Shape CurrentShape(const occ::handle<TNaming_NamedShape>& NS) const;

private:
  bool                       myWithValid;
  NCollection_Map<TDF_Label> myValid;
};

