#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <TDF_Attribute.hpp>
class TopoDS_Shape;
class TNaming_NamedShape;

class TNaming_Selector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool IsIdentified(const TDF_Label&                 access,
                                           const TopoDS_Shape&              selection,
                                           occ::handle<TNaming_NamedShape>& NS,
                                           const bool                       Geometry = false);

  Standard_EXPORT TNaming_Selector(const TDF_Label& aLabel);

  Standard_EXPORT bool Select(const TopoDS_Shape& Selection,
                              const TopoDS_Shape& Context,
                              const bool          Geometry          = false,
                              const bool          KeepOrientatation = false) const;

  Standard_EXPORT bool Select(const TopoDS_Shape& Selection,
                              const bool          Geometry          = false,
                              const bool          KeepOrientatation = false) const;

  Standard_EXPORT bool Solve(NCollection_Map<TDF_Label>& Valid) const;

  Standard_EXPORT void Arguments(NCollection_Map<occ::handle<TDF_Attribute>>& args) const;

  Standard_EXPORT occ::handle<TNaming_NamedShape> NamedShape() const;

private:
  TDF_Label myLabel;
};
