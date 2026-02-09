#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_FindPlane.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Conic.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Line.hpp>
#include <Geom_Parabola.hpp>
#include <Geom_Plane.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>

BRepBuilderAPI_FindPlane::BRepBuilderAPI_FindPlane() = default;

BRepBuilderAPI_FindPlane::BRepBuilderAPI_FindPlane(const TopoDS_Shape& S, const double Tol)
{
  Init(S, Tol);
}

void BRepBuilderAPI_FindPlane::Init(const TopoDS_Shape& S, const double Tol)
{
  double tolerance = Tol;
  myPlane.Nullify();

  TopExp_Explorer ex;
  for (ex.Init(S, TopAbs_EDGE); ex.More(); ex.Next())
  {
    double t = BRep_Tool::Tolerance(TopoDS::Edge(ex.Current()));
    if (t > tolerance)
      tolerance = t;
  }

  double tol2 = tolerance * tolerance;

  TopLoc_Location              loc;
  double                       first, last;
  bool                         found = false;
  occ::handle<Geom_Plane>      P;
  NCollection_Sequence<gp_Pnt> points;
  int                          nbPnts;

  for (ex.Init(S, TopAbs_EDGE); ex.More(); ex.Next())
  {
    occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(TopoDS::Edge(ex.Current()), loc, first, last);

    if (!c3d.IsNull())
    {
      occ::handle<Geom_Curve> c3dptr =
        occ::down_cast<Geom_Curve>(c3d->Transformed(loc.Transformation()));

      occ::handle<Standard_Type> cType = c3dptr->DynamicType();

      if (cType == STANDARD_TYPE(Geom_Line))
      {
        nbPnts = 3;
      }
      else if ((cType == STANDARD_TYPE(Geom_Circle)) || (cType == STANDARD_TYPE(Geom_Ellipse))
               || (cType == STANDARD_TYPE(Geom_Parabola))
               || (cType == STANDARD_TYPE(Geom_Hyperbola)))
      {
        nbPnts = 4;
        if (!found)
        {
          found                      = true;
          occ::handle<Geom_Conic> Co = occ::down_cast<Geom_Conic>(c3dptr);
          P                          = new Geom_Plane(gp_Ax3(Co->Position()));
        }
      }
      else if (cType == STANDARD_TYPE(Geom_BezierCurve))
      {
        occ::handle<Geom_BezierCurve> Co = occ::down_cast<Geom_BezierCurve>(c3dptr);
        nbPnts                           = Co->NbPoles();
      }
      else if (cType == STANDARD_TYPE(Geom_BSplineCurve))
      {
        occ::handle<Geom_BSplineCurve> Co = occ::down_cast<Geom_BSplineCurve>(c3dptr);
        nbPnts                            = Co->NbPoles();
      }
      else
      {
        nbPnts = 10;
      }

      gp_Pnt p0;
      for (int i = 1; i <= nbPnts; i++)
      {
        if (i == 1)
        {
          c3dptr->D0(first, p0);
        }
        else if (i == nbPnts)
        {
          c3dptr->D0(last, p0);
        }
        else
        {
          c3dptr->D0(first + (last - first) / (nbPnts - 1) * (i - 1), p0);
        }
        points.Append(p0);
      }
    }
  }

  if (!found)
  {

    if (points.Length() > 2)
    {

      double disMax = 0.0;
      gp_Pnt p0     = points(1);
      gp_Pnt p1;
      for (int i = 2; i <= points.Length(); i++)
      {
        double dist = p0.SquareDistance(points(i));
        if (dist > disMax)
        {
          disMax = dist;

          p1 = points(i);
        }
      }

      if (disMax > tol2)
      {
        gp_Vec V1(p0, p1), V3;
        double proMax = 0.0;
        gp_Pnt p2     = p0;
        for (int j = 2; j <= points.Length(); j++)
        {
          V3         = V1 ^ gp_Vec(p0, points(j));
          double pro = V3.SquareMagnitude();
          if (pro > proMax)
          {
            proMax = pro;
            p2     = points(j);
          }
        }

        if (p0.SquareDistance(p2) > tol2)
        {
          gp_Dir D1(V1), D2(gp_Vec(p0, p2));
          if (!D1.IsParallel(D2, Precision::Angular()))
          {
            P     = new Geom_Plane(gp_Ax3(p0, D1.Crossed(D2), D1));
            found = true;
          }
        }
      }
    }
  }

  if (found)
  {

    const gp_Pln& pln = P->Pln();
    for (int i = 1; i <= points.Length(); i++)
    {
      if (pln.SquareDistance(points(i)) > tol2)
      {
        found = false;
        break;
      }
    }
  }

  if (found)
  {
    myPlane = P;
  }
}

bool BRepBuilderAPI_FindPlane::Found() const
{
  return !myPlane.IsNull();
}

occ::handle<Geom_Plane> BRepBuilderAPI_FindPlane::Plane() const
{
  return myPlane;
}
