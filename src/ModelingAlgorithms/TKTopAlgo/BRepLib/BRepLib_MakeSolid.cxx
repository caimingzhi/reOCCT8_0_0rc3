#include <BRep_Builder.hpp>
#include <BRepLib_MakeSolid.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_CompSolid.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

//=================================================================================================

BRepLib_MakeSolid::BRepLib_MakeSolid()
{
  BRep_Builder B;
  B.MakeSolid(TopoDS::Solid(myShape));
  Done();
}

//=================================================================================================

BRepLib_MakeSolid::BRepLib_MakeSolid(const TopoDS_CompSolid& S)
{
  BRep_Builder B;
  B.MakeSolid(TopoDS::Solid(myShape));

  TopExp_Explorer                                        ex1, ex2;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMapOfFaces;
  for (ex1.Init(S, TopAbs_SHELL); ex1.More(); ex1.Next())
  {
    for (ex2.Init(ex1.Current(), TopAbs_FACE); ex2.More(); ex2.Next())
    {
      if (!aMapOfFaces.Add(ex2.Current()))
      {
        myDeletedFaces.Append(ex2.Current());
        aMapOfFaces.Remove(ex2.Current());
      }
    }
  }

  TopoDS_Shape aShell;
  B.MakeShell(TopoDS::Shell(aShell));

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aFaceIter(aMapOfFaces);
  for (; aFaceIter.More(); aFaceIter.Next())
  {
    B.Add(aShell, aFaceIter.Key());
  }
  aShell.Closed(BRep_Tool::IsClosed(aShell));

  B.Add(myShape, aShell);

  Done();
}

//=================================================================================================

BRepLib_MakeSolid::BRepLib_MakeSolid(const TopoDS_Shell& S)
{
  BRep_Builder B;
  B.MakeSolid(TopoDS::Solid(myShape));
  B.Add(myShape, S);
  Done();
}

//=================================================================================================

BRepLib_MakeSolid::BRepLib_MakeSolid(const TopoDS_Shell& S1, const TopoDS_Shell& S2)
{
  BRep_Builder B;
  B.MakeSolid(TopoDS::Solid(myShape));
  B.Add(myShape, S1);
  B.Add(myShape, S2);
  Done();
}

//=================================================================================================

BRepLib_MakeSolid::BRepLib_MakeSolid(const TopoDS_Shell& S1,
                                     const TopoDS_Shell& S2,
                                     const TopoDS_Shell& S3)
{
  BRep_Builder B;
  B.MakeSolid(TopoDS::Solid(myShape));
  B.Add(myShape, S1);
  B.Add(myShape, S2);
  B.Add(myShape, S3);
  Done();
}

//=================================================================================================

BRepLib_MakeSolid::BRepLib_MakeSolid(const TopoDS_Solid& So)
{
  BRep_Builder B;
  B.MakeSolid(TopoDS::Solid(myShape));
  TopExp_Explorer ex;
  for (ex.Init(So, TopAbs_SHELL); ex.More(); ex.Next())
    B.Add(myShape, ex.Current());
  Done();
}

//=================================================================================================

BRepLib_MakeSolid::BRepLib_MakeSolid(const TopoDS_Solid& So, const TopoDS_Shell& S)
{
  BRep_Builder B;
  B.MakeSolid(TopoDS::Solid(myShape));
  TopExp_Explorer ex;
  for (ex.Init(So, TopAbs_SHELL); ex.More(); ex.Next())
    B.Add(myShape, ex.Current());
  B.Add(myShape, S);
  Done();
}

//=================================================================================================

void BRepLib_MakeSolid::Add(const TopoDS_Shell& S)
{
  BRep_Builder B;
  B.Add(myShape, S);
}

//=================================================================================================

const TopoDS_Solid& BRepLib_MakeSolid::Solid()
{
  return TopoDS::Solid(Shape());
}

//=================================================================================================

BRepLib_MakeSolid::operator TopoDS_Solid()
{
  return TopoDS::Solid(Shape());
}

//=================================================================================================

BRepLib_ShapeModification BRepLib_MakeSolid::FaceStatus(const TopoDS_Face& F) const
{
  BRepLib_ShapeModification                myStatus = BRepLib_Preserved;
  NCollection_List<TopoDS_Shape>::Iterator anIter(myDeletedFaces);

  for (; anIter.More(); anIter.Next())
  {
    if (F.IsSame(anIter.Value()))
    {
      myStatus = BRepLib_Deleted;
      break;
    }
  }

  return myStatus;
}
