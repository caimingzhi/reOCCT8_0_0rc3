#include <PrsDim_EllipseRadiusDimension.hpp>

#include <PrsDim.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Line.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAPI_ExtremaCurveCurve.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Elips.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_EllipseRadiusDimension, PrsDim_Relation)

PrsDim_EllipseRadiusDimension::PrsDim_EllipseRadiusDimension(
  const TopoDS_Shape&               aShape,
  const TCollection_ExtendedString& aText)

{
  myFShape = aShape;
  myText   = aText;
}

void PrsDim_EllipseRadiusDimension::ComputeGeometry()
{

  switch (myFShape.ShapeType())
  {
    case TopAbs_FACE:
    {

      ComputeFaceGeometry();
      break;
    }
    case TopAbs_EDGE:
    {
      ComputeEdgeGeometry();
      break;
    }
    default:
      break;
  }
  while (myFirstPar > 2 * M_PI)
    myFirstPar -= 2 * M_PI;
  while (myLastPar > 2 * M_PI)
    myLastPar -= 2 * M_PI;
  while (myFirstPar < 0.0)
    myFirstPar += 2 * M_PI;
  while (myLastPar < 0.0)
    myLastPar += 2 * M_PI;
}

void PrsDim_EllipseRadiusDimension::ComputeFaceGeometry()
{

  gp_Pln                    aPln;
  occ::handle<Geom_Surface> aBasisSurf;
  PrsDim_KindOfSurface      aSurfType;
  double                    Offset;
  PrsDim::GetPlaneFromFace(TopoDS::Face(myFShape), aPln, aBasisSurf, aSurfType, Offset);

  if (aSurfType == PrsDim_KOS_Plane)
    ComputePlanarFaceGeometry();
  else
    ComputeCylFaceGeometry(aSurfType, aBasisSurf, Offset);
}

void PrsDim_EllipseRadiusDimension::ComputeCylFaceGeometry(
  const PrsDim_KindOfSurface       aSurfType,
  const occ::handle<Geom_Surface>& aBasisSurf,
  const double                     Offset)
{

  BRepAdaptor_Surface surf1(TopoDS::Face(myFShape));
  double              vFirst, vLast;
  vFirst      = surf1.FirstVParameter();
  vLast       = surf1.LastVParameter();
  double vMid = (vFirst + vLast) * 0.5;
  gp_Pln aPlane;
  gp_Ax1 Axis;

  if (aSurfType == PrsDim_KOS_Extrusion)
  {
    Axis.SetDirection((occ::down_cast<Geom_SurfaceOfLinearExtrusion>(aBasisSurf))->Direction());
    Axis.SetLocation(
      gp_Pnt((occ::down_cast<Geom_SurfaceOfLinearExtrusion>(aBasisSurf))->Direction().XYZ()));

    aPlane.SetAxis(Axis);
    aPlane.SetLocation(myEllipse.Location());
    myPlane = new Geom_Plane(aPlane);

    occ::handle<Geom_Curve> aCurve;
    aCurve = aBasisSurf->VIso(vMid);
    if (aCurve->DynamicType() == STANDARD_TYPE(Geom_Ellipse))
    {
      myEllipse = occ::down_cast<Geom_Ellipse>(aCurve)->Elips();
      myIsAnArc = false;
    }
    else if (aCurve->DynamicType() == STANDARD_TYPE(Geom_TrimmedCurve))
    {
      occ::handle<Geom_TrimmedCurve> tCurve = occ::down_cast<Geom_TrimmedCurve>(aCurve);
      aCurve                                = tCurve->BasisCurve();
      myFirstPar                            = tCurve->FirstParameter();
      myLastPar                             = tCurve->LastParameter();
      myIsAnArc                             = true;
      if (aCurve->DynamicType() == STANDARD_TYPE(Geom_Ellipse))
      {
        myEllipse = occ::down_cast<Geom_Ellipse>(aCurve)->Elips();
      }
    }
    else
    {
      throw Standard_ConstructionError("PrsDim:: Not expected type of surface");
      return;
    }

    if (surf1.GetType() == GeomAbs_OffsetSurface)
    {
      if (Offset < 0.0 && std::abs(Offset) > myEllipse.MinorRadius())
      {
        throw Standard_ConstructionError(
          "PrsDim:: Absolute value of negative offset is larger than MinorRadius");
        return;
      }

      myOffsetCurve  = new Geom_OffsetCurve(new Geom_Ellipse(myEllipse),
                                           Offset,
                                           myPlane->Pln().Axis().Direction());
      myOffset       = Offset;
      myIsOffset     = true;
      gp_Elips elips = myEllipse;
      double   Val   = Offset + elips.MajorRadius();
      myEllipse.SetMajorRadius(Val);
      Val = Offset + elips.MinorRadius();
      myEllipse.SetMinorRadius(Val);
    }
    else
      myIsOffset = false;
  }
}

void PrsDim_EllipseRadiusDimension::ComputePlanarFaceGeometry()
{

  bool            find = false;
  gp_Pnt          ptfirst, ptend;
  TopExp_Explorer ExploEd(TopoDS::Face(myFShape), TopAbs_EDGE);
  for (; ExploEd.More(); ExploEd.Next())
  {
    TopoDS_Edge               curedge = TopoDS::Edge(ExploEd.Current());
    occ::handle<Geom_Curve>   curv;
    occ::handle<Geom_Ellipse> ellips;
    if (PrsDim::ComputeGeometry(curedge, curv, ptfirst, ptend))
    {
      if (curv->DynamicType() == STANDARD_TYPE(Geom_Ellipse))
      {
        ellips = occ::down_cast<Geom_Ellipse>(curv);
        if (!ellips.IsNull())
        {
          myEllipse = ellips->Elips();
          find      = true;
          break;
        }
      }
    }
  }
  if (!find)
  {
    throw Standard_ConstructionError("PrsDim:: Curve is not an ellipsee or is Null");
    return;
  }

  if (!ptfirst.IsEqual(ptend, Precision::Confusion()))
  {
    myIsAnArc  = true;
    myFirstPar = ElCLib::Parameter(myEllipse, ptfirst);
    myLastPar  = ElCLib::Parameter(myEllipse, ptend);
  }
  else
    myIsAnArc = false;

  BRepAdaptor_Surface surfAlgo(TopoDS::Face(myFShape));
  myPlane = new Geom_Plane(surfAlgo.Plane());
}

void PrsDim_EllipseRadiusDimension::ComputeEdgeGeometry()
{
  gp_Pnt                  ptfirst, ptend;
  occ::handle<Geom_Curve> curv;
  if (!PrsDim::ComputeGeometry(TopoDS::Edge(myFShape), curv, ptfirst, ptend))
    return;

  occ::handle<Geom_Ellipse> elips = occ::down_cast<Geom_Ellipse>(curv);
  if (elips.IsNull())
    return;

  myEllipse = elips->Elips();
  gp_Pln aPlane;
  aPlane.SetPosition(gp_Ax3(myEllipse.Position()));
  myPlane = new Geom_Plane(aPlane);

  if (ptfirst.IsEqual(ptend, Precision::Confusion()))
  {
    myIsAnArc = false;
  }
  else
  {
    myIsAnArc  = true;
    myFirstPar = ElCLib::Parameter(myEllipse, ptfirst);
    myLastPar  = ElCLib::Parameter(myEllipse, ptend);
  }
}
