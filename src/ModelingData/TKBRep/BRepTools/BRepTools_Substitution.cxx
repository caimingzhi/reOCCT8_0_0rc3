#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepTools_Substitution.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_NoSuchObject.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>

BRepTools_Substitution::BRepTools_Substitution() = default;

void BRepTools_Substitution::Clear()
{
  myMap.Clear();
}

void BRepTools_Substitution::Substitute(const TopoDS_Shape&                   OS,
                                        const NCollection_List<TopoDS_Shape>& NS)
{
  Standard_ConstructionError_Raise_if(IsCopied(OS), "BRepTools_CutClue::Substitute");
  myMap.Bind(OS, NS);
}

void BRepTools_Substitution::Build(const TopoDS_Shape& S)
{
  if (IsCopied(S))
    return;

  BRep_Builder    B;
  TopoDS_Iterator iteS(S.Oriented(TopAbs_FORWARD));
  bool            IsModified  = false;
  bool            HasSubShape = false;

  for (; iteS.More(); iteS.Next())
  {
    const TopoDS_Shape& SS = iteS.Value();
    Build(SS);
    if (IsCopied(SS))
    {
      IsModified = true;
    }
  }

  TopoDS_Shape NewS = S.Oriented(TopAbs_FORWARD);
  if (IsModified)
  {

    NewS.EmptyCopy();

    if (NewS.ShapeType() == TopAbs_EDGE)
    {
      double f, l;
      BRep_Tool::Range(TopoDS::Edge(S), f, l);
      B.Range(TopoDS::Edge(NewS), f, l);
    }

    iteS.Initialize(S.Oriented(TopAbs_FORWARD));

    for (; iteS.More(); iteS.Next())
    {
      TopAbs_Orientation             OS = iteS.Value().Orientation();
      NCollection_List<TopoDS_Shape> L;
      L = myMap(iteS.Value());
      NCollection_List<TopoDS_Shape>::Iterator iteL(L);

      for (; iteL.More(); iteL.Next())
      {
        const TopoDS_Shape NSS = iteL.Value();

        Build(NSS);

        const NCollection_List<TopoDS_Shape>&    NL    = myMap(NSS);
        TopAbs_Orientation                       NewOr = TopAbs::Compose(OS, NSS.Orientation());
        NCollection_List<TopoDS_Shape>::Iterator iteNL(NL);

        for (; iteNL.More(); iteNL.Next())
        {
          B.Add(NewS, iteNL.Value().Oriented(NewOr));
          HasSubShape = true;
        }
      }
    }
    if (!HasSubShape)
    {
      if (NewS.ShapeType() == TopAbs_WIRE || NewS.ShapeType() == TopAbs_SHELL
          || NewS.ShapeType() == TopAbs_SOLID || NewS.ShapeType() == TopAbs_COMPOUND)

        NewS.Nullify();
    }
  }
  NCollection_List<TopoDS_Shape> L;

  if (!NewS.IsNull())
    L.Append(NewS.Oriented(TopAbs_FORWARD));
  Substitute(S, L);
}

bool BRepTools_Substitution::IsCopied(const TopoDS_Shape& S) const
{
  if (myMap.IsBound(S))
  {
    if (myMap(S).IsEmpty())
      return true;
    else
      return !S.IsSame(myMap(S).First());
  }
  else
    return false;
}

const NCollection_List<TopoDS_Shape>& BRepTools_Substitution::Copy(const TopoDS_Shape& S) const
{
  Standard_NoSuchObject_Raise_if(!IsCopied(S), "BRepTools_Substitution::Copy");
  return myMap(S);
}
