

#include <BRepClass3d_BndBoxTree.hpp>

#include <TopoDS.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <Extrema_ExtPC.hpp>
#include <Extrema_ExtCC.hpp>

bool BRepClass3d_BndBoxTreeSelectorPoint::Accept(const int& theObj)
{

  if (theObj > myMapOfShape.Extent())
    return false;
  const TopoDS_Shape& shp = myMapOfShape(theObj);
  TopAbs_ShapeEnum    sht = shp.ShapeType();
  if (sht == TopAbs_EDGE)
  {
    const TopoDS_Edge& E       = TopoDS::Edge(shp);
    double             EdgeTSq = BRep_Tool::Tolerance(E);
    EdgeTSq *= EdgeTSq;
    double            f, l;
    BRepAdaptor_Curve C(E);
    BRep_Tool::Range(E, f, l);

    Extrema_ExtPC ExtPC(myP, C, f, l);
    if (ExtPC.IsDone() && ExtPC.NbExt() > 0)
    {
      for (int i = 1; i <= ExtPC.NbExt(); i++)
        if (ExtPC.SquareDistance(i) < EdgeTSq)
        {
          myStop = true;
          return true;
        }
    }
  }
  else if (sht == TopAbs_VERTEX)
  {
    const TopoDS_Vertex& V       = TopoDS::Vertex(shp);
    gp_Pnt               VPnt    = BRep_Tool::Pnt(V);
    double               VertTSq = BRep_Tool::Tolerance(V);
    VertTSq *= VertTSq;

    if (VPnt.SquareDistance(myP) < VertTSq)
    {
      myStop = true;
      return true;
    }
  }
  return false;
}

bool BRepClass3d_BndBoxTreeSelectorLine::Accept(const int& theObj)
{

  if (theObj > myMapOfShape.Extent())
    return false;
  const TopoDS_Shape& shp = myMapOfShape(theObj);
  TopAbs_ShapeEnum    sht = shp.ShapeType();
  if (sht == TopAbs_EDGE)
  {
    const TopoDS_Edge& E       = TopoDS::Edge(shp);
    double             EdgeTSq = BRep_Tool::Tolerance(E);
    EdgeTSq *= EdgeTSq;
    double            f, l;
    BRepAdaptor_Curve C(E);
    BRep_Tool::Range(E, f, l);

    Extrema_ExtCC ExtCC(C, myLC, f, l, myLC.FirstParameter(), myLC.LastParameter());
    if (ExtCC.IsDone())
    {
      if (ExtCC.IsParallel())
      {

        myIsValid = false;
      }
      else if (ExtCC.NbExt() > 0)
      {
        bool IsInside = false;
        for (int i = 1; i <= ExtCC.NbExt(); i++)
        {
          if (ExtCC.SquareDistance(i) < EdgeTSq)
          {
            Extrema_POnCurv P1, P2;
            ExtCC.Points(i, P1, P2);

            EdgeParam EP;
            EP.myE      = E;
            EP.myParam  = P1.Parameter();
            EP.myLParam = P2.Parameter();

            myEP.Append(EP);
            IsInside = true;
          }
        }
        if (IsInside)
          return true;
      }
    }
  }
  else if (sht == TopAbs_VERTEX)
  {
    const TopoDS_Vertex& V       = TopoDS::Vertex(shp);
    double               VertTSq = BRep_Tool::Tolerance(V);
    VertTSq *= VertTSq;

    Extrema_ExtPElC ExtPL(BRep_Tool::Pnt(V),
                          myL,
                          Precision::Confusion(),
                          -Precision::Infinite(),
                          Precision::Infinite());
    if (ExtPL.IsDone() && ExtPL.NbExt() > 0)
      if (ExtPL.SquareDistance(1) < VertTSq)
      {
        Extrema_POnCurv PP;
        double          paramL;
        PP     = ExtPL.Point(1);
        paramL = PP.Parameter();
        VertParam VP;
        VP.myV      = V;
        VP.myLParam = paramL;
        myVP.Append(VP);
        return true;
      }
  }
  return false;
}
