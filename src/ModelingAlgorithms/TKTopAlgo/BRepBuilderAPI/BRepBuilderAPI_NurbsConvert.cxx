#include <BRep_Builder.hpp>
#include <BRepBuilderAPI_NurbsConvert.hpp>
#include <BRepLib.hpp>
#include <BRepTools_NurbsConvertModification.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

BRepBuilderAPI_NurbsConvert::BRepBuilderAPI_NurbsConvert()

{
  myModification = new BRepTools_NurbsConvertModification();
}

BRepBuilderAPI_NurbsConvert::BRepBuilderAPI_NurbsConvert(const TopoDS_Shape& S, const bool Copy)

{
  myModification = new BRepTools_NurbsConvertModification();
  Perform(S, Copy);
}

void BRepBuilderAPI_NurbsConvert::Perform(const TopoDS_Shape& S, const bool)
{
  occ::handle<BRepTools_NurbsConvertModification> theModif =
    occ::down_cast<BRepTools_NurbsConvertModification>(myModification);
  DoModif(S, myModification);
  CorrectVertexTol();
}

void BRepBuilderAPI_NurbsConvert::CorrectVertexTol()
{
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> anInitVertices;
  TopExp_Explorer                                        anExp(myInitialShape, TopAbs_VERTEX);
  for (; anExp.More(); anExp.Next())
  {
    anInitVertices.Add(anExp.Current());
  }

  occ::handle<BRepTools_NurbsConvertModification> aModif =
    occ::down_cast<BRepTools_NurbsConvertModification>(myModification);

  BRep_Builder aBB;
  myVtxToReplace.Clear();
  NCollection_List<TopoDS_Shape>::Iterator anEIter(aModif->GetUpdatedEdges());
  for (; anEIter.More(); anEIter.Next())
  {
    const TopoDS_Shape& anE = anEIter.Value();

    double          anETol = BRep_Tool::Tolerance(TopoDS::Edge(anE));
    TopoDS_Iterator anIter(anE);
    for (; anIter.More(); anIter.Next())
    {
      const TopoDS_Vertex& aVtx = TopoDS::Vertex(anIter.Value());
      if (anInitVertices.Contains(aVtx))
      {
        if (myVtxToReplace.IsBound(aVtx))
        {
          aBB.UpdateVertex(TopoDS::Vertex(myVtxToReplace(aVtx)), anETol + Epsilon(anETol));
        }
        else
        {
          double aVTol = BRep_Tool::Tolerance(aVtx);
          if (aVTol < anETol)
          {
            TopoDS_Vertex aNewVtx;
            gp_Pnt        aVPnt = BRep_Tool::Pnt(aVtx);
            aBB.MakeVertex(aNewVtx, aVPnt, anETol + Epsilon(anETol));
            aNewVtx.Orientation(aVtx.Orientation());
            myVtxToReplace.Bind(aVtx, aNewVtx);
          }
        }
      }
      else
      {
        aBB.UpdateVertex(aVtx, anETol + Epsilon(anETol));
      }
    }
  }

  if (myVtxToReplace.IsEmpty())
  {
    return;
  }

  mySubs.Clear();
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator anIter(
    myVtxToReplace);
  for (; anIter.More(); anIter.Next())
  {
    mySubs.Replace(anIter.Key(), anIter.Value());
  }
  mySubs.Apply(myShape);
  myShape = mySubs.Value(myShape);
}

TopoDS_Shape BRepBuilderAPI_NurbsConvert::ModifiedShape(const TopoDS_Shape& S) const
{
  if (S.ShapeType() == TopAbs_VERTEX)
  {
    if (myVtxToReplace.IsBound(S))
    {
      return myVtxToReplace(S);
    }
  }
  if (myVtxToReplace.IsEmpty())
  {
    return myModifier.ModifiedShape(S);
  }
  else
  {
    const TopoDS_Shape& aNS = myModifier.ModifiedShape(S);
    return mySubs.Value(aNS);
  }
}

const NCollection_List<TopoDS_Shape>& BRepBuilderAPI_NurbsConvert::Modified(const TopoDS_Shape& F)
{
  myGenerated.Clear();
  if (F.ShapeType() == TopAbs_VERTEX)
  {
    if (myVtxToReplace.IsBound(F))
    {
      myGenerated.Append(myVtxToReplace(F));
    }
    else
    {
      myGenerated.Append(myModifier.ModifiedShape(F));
    }
  }
  else
  {
    if (myVtxToReplace.IsEmpty())
    {
      myGenerated.Append(myModifier.ModifiedShape(F));
    }
    else
    {
      const TopoDS_Shape& aNS = myModifier.ModifiedShape(F);
      myGenerated.Append(mySubs.Value(aNS));
    }
  }
  return myGenerated;
}
