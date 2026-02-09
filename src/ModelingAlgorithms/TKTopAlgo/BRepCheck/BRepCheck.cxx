#include <BRepCheck.hpp>

#include <BRep_Tool.hpp>
#include <BRepCheck_Status.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Shared.hpp>
#include <BRepCheck_Wire.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Wire.hpp>
#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <gp_Elips.hpp>

void BRepCheck::Add(NCollection_List<BRepCheck_Status>& lst, const BRepCheck_Status stat)
{
  NCollection_List<BRepCheck_Status>::Iterator it(lst);
  while (it.More())
  {
    if (it.Value() == BRepCheck_NoError && stat != BRepCheck_NoError)
    {
      lst.Remove(it);
    }
    else
    {
      if (it.Value() == stat)
      {
        return;
      }
      it.Next();
    }
  }
  lst.Append(stat);
}

bool BRepCheck::SelfIntersection(const TopoDS_Wire& W,
                                 const TopoDS_Face& myFace,
                                 TopoDS_Edge&       RetE1,
                                 TopoDS_Edge&       RetE2)
{
  occ::handle<BRepCheck_Wire> chkw = new BRepCheck_Wire(W);
  BRepCheck_Status            stat = chkw->SelfIntersect(myFace, RetE1, RetE2);
  return (stat == BRepCheck_SelfIntersectingWire);
}

double BRepCheck::PrecCurve(const Adaptor3d_Curve& aAC3D)
{
  double aXEmax = RealEpsilon();

  GeomAbs_CurveType aCT = aAC3D.GetType();
  if (aCT == GeomAbs_Ellipse)
  {
    double aX[5];

    gp_Elips aEL3D = aAC3D.Ellipse();
    aEL3D.Location().Coord(aX[0], aX[1], aX[2]);
    aX[3]  = aEL3D.MajorRadius();
    aX[4]  = aEL3D.MinorRadius();
    aXEmax = -1.;
    for (int i = 0; i < 5; ++i)
    {
      if (aX[i] < 0.)
      {
        aX[i] = -aX[i];
      }
      double aXE = Epsilon(aX[i]);
      if (aXE > aXEmax)
      {
        aXEmax = aXE;
      }
    }
  }

  return aXEmax;
}

double BRepCheck::PrecSurface(const occ::handle<Adaptor3d_Surface>& aAHSurf)
{
  double aXEmax = RealEpsilon();

  GeomAbs_SurfaceType aST = aAHSurf->GetType();
  if (aST == GeomAbs_Cone)
  {
    gp_Cone aCone = aAHSurf->Cone();
    double  aX[4];

    aCone.Location().Coord(aX[0], aX[1], aX[2]);
    aX[3]  = aCone.RefRadius();
    aXEmax = -1.;
    for (int i = 0; i < 4; ++i)
    {
      if (aX[i] < 0.)
      {
        aX[i] = -aX[i];
      }
      double aXE = Epsilon(aX[i]);
      if (aXE > aXEmax)
      {
        aXEmax = aXE;
      }
    }
  }
  return aXEmax;
}

void BRepCheck::Print(const BRepCheck_Status stat, Standard_OStream& OS)
{

  switch (stat)
  {
    case BRepCheck_NoError:
      OS << "BRepCheck_NoError\n";
      break;
    case BRepCheck_InvalidPointOnCurve:
      OS << "BRepCheck_InvalidPointOnCurve\n";
      break;
    case BRepCheck_InvalidPointOnCurveOnSurface:
      OS << "BRepCheck_InvalidPointOnCurveOnSurface\n";
      break;
    case BRepCheck_InvalidPointOnSurface:
      OS << "BRepCheck_InvalidPointOnSurface\n";
      break;
    case BRepCheck_No3DCurve:
      OS << "BRepCheck_No3DCurve\n";
      break;
    case BRepCheck_Multiple3DCurve:
      OS << "BRepCheck_Multiple3DCurve\n";
      break;
    case BRepCheck_Invalid3DCurve:
      OS << "BRepCheck_Invalid3DCurve\n";
      break;
    case BRepCheck_NoCurveOnSurface:
      OS << "BRepCheck_NoCurveOnSurface\n";
      break;
    case BRepCheck_InvalidCurveOnSurface:
      OS << "BRepCheck_InvalidCurveOnSurface\n";
      break;
    case BRepCheck_InvalidCurveOnClosedSurface:
      OS << "BRepCheck_InvalidCurveOnClosedSurface\n";
      break;
    case BRepCheck_InvalidSameRangeFlag:
      OS << "BRepCheck_InvalidSameRangeFlag\n";
      break;
    case BRepCheck_InvalidSameParameterFlag:
      OS << "BRepCheck_InvalidSameParameterFlag\n";
      break;
    case BRepCheck_InvalidDegeneratedFlag:
      OS << "BRepCheck_InvalidDegeneratedFlag\n";
      break;
    case BRepCheck_FreeEdge:
      OS << "BRepCheck_FreeEdge\n";
      break;
    case BRepCheck_InvalidMultiConnexity:
      OS << "BRepCheck_InvalidMultiConnexity\n";
      break;
    case BRepCheck_InvalidRange:
      OS << "BRepCheck_InvalidRange\n";
      break;
    case BRepCheck_EmptyWire:
      OS << "BRepCheck_EmptyWire\n";
      break;
    case BRepCheck_RedundantEdge:
      OS << "BRepCheck_RedundantEdge\n";
      break;
    case BRepCheck_SelfIntersectingWire:
      OS << "BRepCheck_SelfIntersectingWire\n";
      break;
    case BRepCheck_NoSurface:
      OS << "BRepCheck_NoSurface\n";
      break;
    case BRepCheck_InvalidWire:
      OS << "BRepCheck_InvalidWire\n";
      break;
    case BRepCheck_RedundantWire:
      OS << "BRepCheck_RedundantWire\n";
      break;
    case BRepCheck_IntersectingWires:
      OS << "BRepCheck_IntersectingWires\n";
      break;
    case BRepCheck_InvalidImbricationOfWires:
      OS << "BRepCheck_InvalidImbricationOfWires\n";
      break;
    case BRepCheck_EmptyShell:
      OS << "BRepCheck_EmptyShell\n";
      break;
    case BRepCheck_RedundantFace:
      OS << "BRepCheck_RedundantFace\n";
      break;
    case BRepCheck_UnorientableShape:
      OS << "BRepCheck_UnorientableShape\n";
      break;
    case BRepCheck_NotClosed:
      OS << "BRepCheck_NotClosed\n";
      break;
    case BRepCheck_NotConnected:
      OS << "BRepCheck_NotConnected\n";
      break;
    case BRepCheck_SubshapeNotInShape:
      OS << "BRepCheck_SubshapeNotInShape\n";
      break;
    case BRepCheck_BadOrientation:
      OS << "BRepCheck_BadOrientation\n";
      break;
    case BRepCheck_BadOrientationOfSubshape:
      OS << "BRepCheck_BadOrientationOfSubshape\n";
      break;
    case BRepCheck_CheckFail:
      OS << "BRepCheck_CheckFail\n";
      break;
    case BRepCheck_InvalidPolygonOnTriangulation:
      OS << "BRepCheck_InvalidPolygonOnTriangulation\n";
      break;
    case BRepCheck_InvalidToleranceValue:
      OS << "BRepCheck_InvalidToleranceValue\n";
      break;
    case BRepCheck_InvalidImbricationOfShells:
      OS << "BRepCheck_InvalidImbricationOfShells\n";
      break;
    case BRepCheck_EnclosedRegion:
      OS << "BRepCheck_EnclosedRegion\n";
      break;
    default:
      break;
  }
}
