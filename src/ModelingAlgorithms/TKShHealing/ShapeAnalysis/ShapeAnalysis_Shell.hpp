#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Shape;
class TopoDS_Compound;

class ShapeAnalysis_Shell
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeAnalysis_Shell();

  Standard_EXPORT void Clear();

  Standard_EXPORT void LoadShells(const TopoDS_Shape& shape);

  Standard_EXPORT bool CheckOrientedShells(const TopoDS_Shape& shape,
                                           const bool          alsofree           = false,
                                           const bool          checkinternaledges = false);

  Standard_EXPORT bool IsLoaded(const TopoDS_Shape& shape) const;

  Standard_EXPORT int NbLoaded() const;

  Standard_EXPORT TopoDS_Shape Loaded(const int num) const;

  Standard_EXPORT bool HasBadEdges() const;

  Standard_EXPORT TopoDS_Compound BadEdges() const;

  Standard_EXPORT bool HasFreeEdges() const;

  Standard_EXPORT TopoDS_Compound FreeEdges() const;

  Standard_EXPORT bool HasConnectedEdges() const;

private:
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myShells;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myBad;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myFree;
  bool                                                          myConex;
};
