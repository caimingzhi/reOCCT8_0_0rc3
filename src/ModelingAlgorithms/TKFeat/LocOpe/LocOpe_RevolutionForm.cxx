#include <BRepLib_MakeVertex.hpp>
#include <BRepSweep_Revol.hpp>
#include <BRepTools_Modifier.hpp>
#include <BRepTools_TrsfModification.hpp>
#include <Geom_Circle.hpp>
#include <gp_Ax1.hpp>
#include <gp_Trsf.hpp>
#include <LocOpe_BuildShape.hpp>
#include <LocOpe_RevolutionForm.hpp>
#include <StdFail_NotDone.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

LocOpe_RevolutionForm::LocOpe_RevolutionForm()
    : myAngle(0.0),
      myAngTra(0.0),
      myDone(false),
      myIsTrans(false)
{
}

void LocOpe_RevolutionForm::Perform(const TopoDS_Shape& Base,
                                    const gp_Ax1&       Axis,
                                    const double        Angle)
{
  myMap.Clear();
  myFirstShape.Nullify();
  myLastShape.Nullify();
  myBase.Nullify();
  myRes.Nullify();
  myBase    = Base;
  myAngle   = Angle;
  myAxis    = Axis;
  myAngTra  = 0.;
  myIsTrans = false;
  IntPerf();
}

void LocOpe_RevolutionForm::IntPerf()
{
  TopoDS_Shape       theBase = myBase;
  BRepTools_Modifier Modif;
  if (myIsTrans)
  {
    gp_Trsf T;
    T.SetRotation(myAxis, myAngTra);
    occ::handle<BRepTools_TrsfModification> modbase = new BRepTools_TrsfModification(T);
    Modif.Init(theBase);
    Modif.Perform(modbase);
    theBase = Modif.ModifiedShape(theBase);
  }

  BRepSweep_Revol theRevol(theBase, myAxis, myAngle);

  myFirstShape = theRevol.FirstShape();
  myLastShape  = theRevol.LastShape();

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
        TopoDS_Shape desc = theRevol.Shape(edg);
        if (!desc.IsNull())
        {
          myMap(edg).Append(desc);
        }
      }
    }
    myRes = theRevol.Shape();
  }

  else
  {

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
      TopoDS_Shape desc = theRevol.Shape(edg);
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
          TopoDS_Shape desc = theRevol.Shape(edg);
          if (!desc.IsNull())
          {
            myMap(edg).Append(desc);
          }
        }
      }
      myRes = theRevol.Shape();
    }
  }

  if (myIsTrans)
  {

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

const TopoDS_Shape& LocOpe_RevolutionForm::Shape() const
{
  if (!myDone)
  {
    throw StdFail_NotDone();
  }
  return myRes;
}

const TopoDS_Shape& LocOpe_RevolutionForm::FirstShape() const
{
  return myFirstShape;
}

const TopoDS_Shape& LocOpe_RevolutionForm::LastShape() const
{
  return myLastShape;
}

const NCollection_List<TopoDS_Shape>& LocOpe_RevolutionForm::Shapes(const TopoDS_Shape& S) const
{
  return myMap(S);
}
