

#include <BRep_Tool.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDSToStep_FacetedTool.hpp>

TopoDSToStep_FacetedError TopoDSToStep_FacetedTool::CheckTopoDSShape(const TopoDS_Shape& aShape)
{
  TopExp_Explorer FaceExp, EdgeExp;
  FaceExp.Init(aShape, TopAbs_FACE);
  while (FaceExp.More())
  {
    const TopoDS_Face aFace = TopoDS::Face(FaceExp.Current());
    FaceExp.Next();

    occ::handle<Geom_Surface> Su = BRep_Tool::Surface(aFace);

    if (Su->IsKind(STANDARD_TYPE(Geom_Plane)))
    {
    }
    else if (Su->IsKind(STANDARD_TYPE(Geom_BSplineSurface)))
    {
      occ::handle<Geom_BSplineSurface> aBsplS = occ::down_cast<Geom_BSplineSurface>(Su);
      int                              uDeg, vDeg, nUPol, nVPol;
      uDeg = aBsplS->UDegree();
      if (uDeg == 1)
      {
        vDeg = aBsplS->VDegree();
        if (vDeg == 1)
        {
          nUPol = aBsplS->NbUPoles();
          nVPol = aBsplS->NbVPoles();
          if (nUPol != 2 || nVPol != 2)
          {
            return TopoDSToStep_SurfaceNotPlane;
          }
        }
        else
        {

          return TopoDSToStep_SurfaceNotPlane;
        }
      }
      else
      {

        return TopoDSToStep_SurfaceNotPlane;
      }
    }
    else if (Su->IsKind(STANDARD_TYPE(Geom_BezierSurface)))
    {
      occ::handle<Geom_BezierSurface> aBzS = occ::down_cast<Geom_BezierSurface>(Su);
      int                             uDeg, vDeg, nUPol, nVPol;
      uDeg = aBzS->UDegree();
      if (uDeg == 1)
      {
        vDeg = aBzS->VDegree();
        if (vDeg == 1)
        {
          nUPol = aBzS->NbUPoles();
          nVPol = aBzS->NbVPoles();
          if (nUPol != 2 || nVPol != 2)
          {
            return TopoDSToStep_SurfaceNotPlane;
          }
        }
        else
        {

          return TopoDSToStep_SurfaceNotPlane;
        }
      }
      else
      {

        return TopoDSToStep_SurfaceNotPlane;
      }
    }
    else
    {

      return TopoDSToStep_SurfaceNotPlane;
    }

    EdgeExp.Init(aFace, TopAbs_EDGE);
    while (EdgeExp.More())
    {
      const TopoDS_Edge anEdge = TopoDS::Edge(EdgeExp.Current());
      EdgeExp.Next();

      double                    cf, cl;
      occ::handle<Geom2d_Curve> C2d = BRep_Tool::CurveOnSurface(anEdge, aFace, cf, cl);

      if (C2d->IsKind(STANDARD_TYPE(Geom2d_Line)))
      {
        return TopoDSToStep_FacetedDone;
      }
      else if (C2d->IsKind(STANDARD_TYPE(Geom2d_BSplineCurve)))
      {
        occ::handle<Geom2d_BSplineCurve> aBspl2d = occ::down_cast<Geom2d_BSplineCurve>(C2d);
        if ((aBspl2d->Degree() != 1) || (aBspl2d->NbPoles() != 2))
        {
          return TopoDSToStep_PCurveNotLinear;
        }
      }
      else if (C2d->IsKind(STANDARD_TYPE(Geom2d_BezierCurve)))
      {
        occ::handle<Geom2d_BezierCurve> aBzC2d = occ::down_cast<Geom2d_BezierCurve>(C2d);
        if ((aBzC2d->Degree() != 1) || (aBzC2d->NbPoles() != 2))
        {
          return TopoDSToStep_PCurveNotLinear;
        }
      }
      else
      {
        return TopoDSToStep_PCurveNotLinear;
      }
    }
  }

  return TopoDSToStep_FacetedDone;
}
