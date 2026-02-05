#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <GeomTools_Curve2dSet.hpp>
#include <GeomTools_CurveSet.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <TCollection_AsciiString.hpp>
#include <TopOpeBRepDS.hpp>
#include <TopOpeBRepDS_CurveExplorer.hpp>
#include <TopOpeBRepDS_define.hpp>
#include <TopOpeBRepDS_Dumper.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>

//=================================================================================================

TopOpeBRepDS_Dumper::TopOpeBRepDS_Dumper(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  myHDS = HDS;
}

//=================================================================================================

TCollection_AsciiString TopOpeBRepDS_Dumper::SDumpRefOri(const TopOpeBRepDS_Kind K,
                                                         const int               I) const
{
  TCollection_AsciiString           SS;
  bool                              fk = false;
  const TopOpeBRepDS_DataStructure& DS = myHDS->DS();
  if (!TopOpeBRepDS::IsTopology(K))
    return SS;
  TopAbs_ShapeEnum t = TopOpeBRepDS::KindToShape(K);
  if (DS.Shape(I, fk).ShapeType() != t)
    return SS;
  const TopoDS_Shape& S = myHDS->Shape(I, fk);
  int                 r = myHDS->SameDomainReference(S);
  TopOpeBRepDS_Config o = myHDS->SameDomainOrientation(S);
  SS                    = SS + "(" + SPrintShape(r) + "," + TopOpeBRepDS::SPrint(o) + ")";
  return SS;
}

//=================================================================================================

TCollection_AsciiString TopOpeBRepDS_Dumper::SDumpRefOri(const TopoDS_Shape& S) const
{
  TCollection_AsciiString SS;
  TopOpeBRepDS_Kind       k  = TopOpeBRepDS::ShapeToKind(S.ShapeType());
  bool                    fk = false;
  int                     i  = myHDS->Shape(S, fk);
  SS                         = SDumpRefOri(k, i);
  return SS;
}

//=================================================================================================

TCollection_AsciiString TopOpeBRepDS_Dumper::SPrintShape(const int IS) const
{
  TCollection_AsciiString           SS;
  const TopOpeBRepDS_DataStructure& BDS = myHDS->DS();
  if (IS < 1 || IS > BDS.NbShapes())
    return SS;
  SS = SPrintShape(BDS.Shape(IS));
  return SS;
}

//=================================================================================================

TCollection_AsciiString TopOpeBRepDS_Dumper::SPrintShape(const TopoDS_Shape& S) const
{
  const TopOpeBRepDS_DataStructure& BDS    = myHDS->DS();
  const int                         IS     = myHDS->DS().Shape(S);
  int                               rankIS = BDS.AncestorRank(IS);
  // JR/Hp  TCollection_AsciiString s1,s2;
  const char* s1;
  const char* s2;
  if (BDS.KeepShape(IS))
  {
    s1 = (const char*)((rankIS == 1) ? "*" : "");
    s2 = (const char*)((rankIS == 2) ? "*" : "");
  }
  else
  {
    s1 = (const char*)((rankIS == 1) ? "~" : "");
    s2 = (const char*)((rankIS == 2) ? "~" : "");
  }
  TCollection_AsciiString sse =
    TopOpeBRepDS::SPrint(TopOpeBRepDS::ShapeToKind(S.ShapeType()), IS, s1, s2);
  return sse;
}

//=================================================================================================

TCollection_AsciiString TopOpeBRepDS_Dumper::SPrintShapeRefOri(
  const TopoDS_Shape&            S,
  const TCollection_AsciiString& astr) const
{
  TCollection_AsciiString SS = astr + SPrintShape(S) + " " + SDumpRefOri(S);
  return SS;
}

//=================================================================================================

TCollection_AsciiString TopOpeBRepDS_Dumper::SPrintShapeRefOri(
  const NCollection_List<TopoDS_Shape>& L,
  const TCollection_AsciiString&        astr) const
{
  TCollection_AsciiString                  SS;
  NCollection_List<TopoDS_Shape>::Iterator it(L);
  if (!it.More())
    return SS;
  SS = SS + astr;
  TCollection_AsciiString bst(astr.Length(), ' ');
  for (int il = 0; it.More(); it.Next(), il++)
  {
    TCollection_AsciiString ss = SPrintShapeRefOri(it.Value());
    if (il)
      ss = bst + ss;
    SS = SS + ss + "\n";
  }
  return SS;
}
