#include <BRep_Builder.hpp>
#include <BRepBuilderAPI_GTransform.hpp>
#include <BRepBuilderAPI_NurbsConvert.hpp>
#include <BRepTools_GTrsfModification.hpp>
#include <BRepTools_NurbsConvertModification.hpp>
#include <gp_GTrsf.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

//=================================================================================================

BRepBuilderAPI_GTransform::BRepBuilderAPI_GTransform(const gp_GTrsf& T)
    : myGTrsf(T)
{
  myModification = new BRepTools_GTrsfModification(T);
}

//=================================================================================================

BRepBuilderAPI_GTransform::BRepBuilderAPI_GTransform(const TopoDS_Shape& S,
                                                     const gp_GTrsf&     T,
                                                     const bool          Copy)
    : myGTrsf(T)
{
  myModification = new BRepTools_GTrsfModification(T);
  Perform(S, Copy);
}

//=================================================================================================

void BRepBuilderAPI_GTransform::Perform(const TopoDS_Shape& S, const bool Copy)
{
  BRepBuilderAPI_NurbsConvert nc;
  nc.Perform(S, Copy);
  myHist.Add(S, nc);
  TopoDS_Shape                             Slocal = nc.Shape();
  occ::handle<BRepTools_GTrsfModification> theModif =
    occ::down_cast<BRepTools_GTrsfModification>(myModification);
  theModif->GTrsf() = myGTrsf;
  DoModif(Slocal, myModification);
  //  myHist.Filter (Shape());
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& BRepBuilderAPI_GTransform::Modified(const TopoDS_Shape& F)
{
  myGenerated.Clear();
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    M = myHist.Modification();
  if (M.IsBound(F))
  {
    NCollection_List<TopoDS_Shape>           Li;
    NCollection_List<TopoDS_Shape>::Iterator itL(M(F));
    for (; itL.More(); itL.Next())
      Li.Assign(BRepBuilderAPI_ModifyShape::Modified(itL.Value()));
  }
  return myGenerated;
}

//=================================================================================================

TopoDS_Shape BRepBuilderAPI_GTransform::ModifiedShape(const TopoDS_Shape& S) const
{
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
               aMapModif = myHist.Modification();
  TopoDS_Shape aShape    = S;

  if (aMapModif.IsBound(S))
  {
    const NCollection_List<TopoDS_Shape>& aListModShape = aMapModif(S);
    int                                   aNbShapes     = aListModShape.Extent();

    if (aNbShapes > 0)
      aShape = aListModShape.First();
  }

  return BRepBuilderAPI_ModifyShape::ModifiedShape(aShape);
}
