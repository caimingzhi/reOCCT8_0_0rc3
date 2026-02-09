#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
class ShapeBuild_ReShape;
class TopoDS_Shape;

class ShapeUpgrade_ShellSewing
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeUpgrade_ShellSewing();

  Standard_EXPORT TopoDS_Shape ApplySewing(const TopoDS_Shape& shape, const double tol = 0.0);

private:
  Standard_EXPORT void Init(const TopoDS_Shape& shape);

  Standard_EXPORT int Prepare(const double tol);

  Standard_EXPORT TopoDS_Shape Apply(const TopoDS_Shape& shape, const double tol);

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myShells;
  occ::handle<ShapeBuild_ReShape>                               myReShape;
};
