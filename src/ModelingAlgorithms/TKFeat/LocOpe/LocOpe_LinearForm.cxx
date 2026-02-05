#include <BRep_Builder.hpp>
#include <BRepSweep_Prism.hpp>
#include <BRepTools_Modifier.hpp>
#include <BRepTools_TrsfModification.hpp>
#include <Geom_Line.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <LocOpe_BuildShape.hpp>
#include <LocOpe_LinearForm.hpp>
#include <StdFail_NotDone.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

//=================================================================================================

void LocOpe_LinearForm::Perform(const TopoDS_Shape& Base,
                                const gp_Vec&       V,
                                const gp_Pnt&       Pnt1,
                                const gp_Pnt&       Pnt2)

{
  myIsTrans = false;
  myMap.Clear();
  myFirstShape.Nullify();
  myLastShape.Nullify();
  myBase.Nullify();
  myRes.Nullify();

  myBase = Base;
  myVec  = V;

  // myEdge = E;
  myPnt1 = Pnt1;
  myPnt2 = Pnt2;

  IntPerf();
}

//=================================================================================================

void LocOpe_LinearForm::Perform(const TopoDS_Shape& Base,
                                const gp_Vec&       V,
                                const gp_Vec&       Vectra,
                                const gp_Pnt&       Pnt1,
                                const gp_Pnt&       Pnt2)

{
  myIsTrans = true;
  myTra     = Vectra;
  myMap.Clear();
  myFirstShape.Nullify();
  myLastShape.Nullify();
  myBase.Nullify();
  myRes.Nullify();

  myBase = Base;
  myVec  = V;

  // myEdge = E;
  myPnt1 = Pnt1;
  myPnt2 = Pnt2;

  IntPerf();
}

//=================================================================================================

void LocOpe_LinearForm::IntPerf()
{
  TopoDS_Shape       theBase = myBase;
  BRepTools_Modifier Modif;

  if (myIsTrans)
  {
    gp_Trsf T;
    T.SetTranslation(myTra);
    occ::handle<BRepTools_TrsfModification> modbase = new BRepTools_TrsfModification(T);
    Modif.Init(theBase);
    Modif.Perform(modbase);
    theBase = Modif.ModifiedShape(theBase);
  }

  BRepSweep_Prism myPrism(theBase, myVec);

  myFirstShape = myPrism.FirstShape();
  myLastShape  = myPrism.LastShape();

  TopExp_Explorer exp;
  if (theBase.ShapeType() == TopAbs_FACE)
  {
    for (exp.Init(theBase, TopAbs_EDGE); exp.More(); exp.Next())
    {
      const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
      if (!myMap.IsBound(edg))
      {
        NCollection_List<TopoDS_Shape> thelist;
        myMap.Bind(edg, thelist);
        TopoDS_Shape desc = myPrism.Shape(edg);
        if (!desc.IsNull())
        {
          myMap(edg).Append(desc);
        }
      }
    }
    myRes = myPrism.Shape();
  }

  else
  {
    // Cas base != FACE
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>
      theEFMap;
    TopExp::MapShapesAndAncestors(theBase, TopAbs_EDGE, TopAbs_FACE, theEFMap);
    NCollection_List<TopoDS_Shape> lfaces;
    bool                           toremove = false;
    for (int i = 1; i <= theEFMap.Extent(); i++)
    {
      const TopoDS_Shape&            edg = theEFMap.FindKey(i);
      NCollection_List<TopoDS_Shape> thelist1;
      myMap.Bind(edg, thelist1);
      TopoDS_Shape desc = myPrism.Shape(edg);
      if (!desc.IsNull())
      {
        if (theEFMap(i).Extent() >= 2)
        {
          toremove = true;
        }
        else
        {
          myMap(edg).Append(desc);
          lfaces.Append(desc);
        }
      }
    }
    if (toremove)
    {
      // Rajouter les faces de FirstShape et LastShape
      for (exp.Init(myFirstShape, TopAbs_FACE); exp.More(); exp.Next())
      {
        lfaces.Append(exp.Current());
      }
      for (exp.Init(myLastShape, TopAbs_FACE); exp.More(); exp.Next())
      {
        lfaces.Append(exp.Current());
      }

      LocOpe_BuildShape BS(lfaces);
      myRes = BS.Shape();
    }
    else
    {
      for (exp.Init(theBase, TopAbs_EDGE); exp.More(); exp.Next())
      {
        const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
        if (!myMap.IsBound(edg))
        {
          NCollection_List<TopoDS_Shape> thelist2;
          myMap.Bind(edg, thelist2);
          TopoDS_Shape desc = myPrism.Shape(edg);
          if (!desc.IsNull())
          {
            myMap(edg).Append(desc);
          }
        }
      }
      myRes = myPrism.Shape();
    }
  }

  if (myIsTrans)
  {
    // m-a-j des descendants
    TopExp_Explorer anExp;
    for (anExp.Init(myBase, TopAbs_EDGE); anExp.More(); anExp.Next())
    {
      const TopoDS_Edge& edg    = TopoDS::Edge(anExp.Current());
      const TopoDS_Edge& edgbis = TopoDS::Edge(Modif.ModifiedShape(edg));
      if (!edgbis.IsSame(edg) && myMap.IsBound(edgbis))
      {
        myMap.Bind(edg, myMap(edgbis));
        myMap.UnBind(edgbis);
      }
    }
  }

  myDone = true;
}

//=================================================================================================

const TopoDS_Shape& LocOpe_LinearForm::Shape() const
{
  if (!myDone)
  {
    throw StdFail_NotDone();
  }
  return myRes;
}

//=================================================================================================

const TopoDS_Shape& LocOpe_LinearForm::FirstShape() const
{
  return myFirstShape;
}

//=================================================================================================

const TopoDS_Shape& LocOpe_LinearForm::LastShape() const
{
  return myLastShape;
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& LocOpe_LinearForm::Shapes(const TopoDS_Shape& S) const
{
  return myMap(S);
}
