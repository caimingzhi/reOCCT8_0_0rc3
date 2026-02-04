#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
class ShapeBuild_ReShape;
class TopoDS_Shape;

//! This class provides a tool for applying sewing algorithm from
//! BRepBuilderAPI: it takes a shape, calls sewing for each shell,
//! and then replaces sewed shells with use of ShapeBuild_ReShape
class ShapeUpgrade_ShellSewing
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a ShellSewing, empty
  Standard_EXPORT ShapeUpgrade_ShellSewing();

  //! Builds a new shape from a former one, by calling Sewing from
  //! BRepBuilderAPI. Rebuilt solids are oriented to be "not infinite"
  //!
  //! If <tol> is not given (i.e. value 0. by default), it is
  //! computed as the mean tolerance recorded in <shape>
  //!
  //! If no shell has been sewed, this method returns the input
  //! shape
  Standard_EXPORT TopoDS_Shape ApplySewing(const TopoDS_Shape& shape, const double tol = 0.0);

private:
  Standard_EXPORT void Init(const TopoDS_Shape& shape);

  Standard_EXPORT int Prepare(const double tol);

  Standard_EXPORT TopoDS_Shape Apply(const TopoDS_Shape& shape, const double tol);

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myShells;
  occ::handle<ShapeBuild_ReShape>                               myReShape;
};

