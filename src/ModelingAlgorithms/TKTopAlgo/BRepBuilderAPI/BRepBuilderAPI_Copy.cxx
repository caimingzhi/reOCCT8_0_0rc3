#include <BRepBuilderAPI_Copy.hpp>
#include <BRepTools_CopyModification.hpp>

//=================================================================================================

BRepBuilderAPI_Copy::BRepBuilderAPI_Copy()
{
  myModification = new BRepTools_CopyModification(true, false);
}

//=================================================================================================

BRepBuilderAPI_Copy::BRepBuilderAPI_Copy(const TopoDS_Shape& S,
                                         const bool          copyGeom,
                                         const bool          copyMesh)
{
  myModification = new BRepTools_CopyModification(copyGeom, copyMesh);
  DoModif(S);
}

//=================================================================================================

void BRepBuilderAPI_Copy::Perform(const TopoDS_Shape& S, const bool copyGeom, const bool copyMesh)
{
  myModification = new BRepTools_CopyModification(copyGeom, copyMesh);
  NotDone(); // on force la copie si on vient deja d`en faire une
  DoModif(S);
}
