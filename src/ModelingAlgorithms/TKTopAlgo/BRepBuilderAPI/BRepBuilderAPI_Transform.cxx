#include <BRepBuilderAPI_Transform.hpp>
#include <BRepTools_TrsfModification.hpp>
#include <gp_Trsf.hpp>
#include <TopoDS_Shape.hpp>

BRepBuilderAPI_Transform::BRepBuilderAPI_Transform(const gp_Trsf& T)
    : myTrsf(T)
{
  myModification = new BRepTools_TrsfModification(T);
}

BRepBuilderAPI_Transform::BRepBuilderAPI_Transform(const TopoDS_Shape& theShape,
                                                   const gp_Trsf&      theTrsf,
                                                   const bool          theCopyGeom,
                                                   const bool          theCopyMesh)
    : myTrsf(theTrsf)
{
  myModification = new BRepTools_TrsfModification(theTrsf);
  Perform(theShape, theCopyGeom, theCopyMesh);
}

void BRepBuilderAPI_Transform::Perform(const TopoDS_Shape& theShape,
                                       const bool          theCopyGeom,
                                       const bool          theCopyMesh)
{
  myUseModif = theCopyGeom || myTrsf.IsNegative()
               || (std::abs(std::abs(myTrsf.ScaleFactor()) - 1.) > TopLoc_Location::ScalePrec());
  if (myUseModif)
  {
    occ::handle<BRepTools_TrsfModification> theModif =
      occ::down_cast<BRepTools_TrsfModification>(myModification);
    theModif->Trsf()       = myTrsf;
    theModif->IsCopyMesh() = theCopyMesh;
    DoModif(theShape, myModification);
  }
  else
  {
    myLocation = myTrsf;
    myShape    = theShape.Moved(myLocation);
    Done();
  }
}

TopoDS_Shape BRepBuilderAPI_Transform::ModifiedShape(const TopoDS_Shape& S) const
{
  if (myUseModif)
  {
    return myModifier.ModifiedShape(S);
  }
  return S.Moved(myLocation);
}

const NCollection_List<TopoDS_Shape>& BRepBuilderAPI_Transform::Modified(const TopoDS_Shape& F)
{
  if (!myUseModif)
  {
    myGenerated.Clear();
    myGenerated.Append(F.Moved(myLocation));
    return myGenerated;
  }
  return BRepBuilderAPI_ModifyShape::Modified(F);
}
