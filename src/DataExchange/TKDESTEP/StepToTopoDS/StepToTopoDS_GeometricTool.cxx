#include <BRep_Builder.hpp>
#include <BRepTools.hpp>
#include <ElCLib.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <GeomAPI_ProjectPointOnSurf.hpp>
#include <Precision.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>
#include <StepGeom_Line.hpp>
#include <StepGeom_Pcurve.hpp>
#include <StepGeom_SeamCurve.hpp>
#include <StepGeom_Surface.hpp>
#include <StepGeom_SurfaceCurve.hpp>
#include <StepGeom_Vector.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>
#include <StepShape_EdgeLoop.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <StepToTopoDS.hpp>
#include <StepToTopoDS_GeometricTool.hpp>
#include <Transfer_TransientProcess.hpp>

int StepToTopoDS_GeometricTool::PCurve(const occ::handle<StepGeom_SurfaceCurve>& SurfCurve,
                                       const occ::handle<StepGeom_Surface>&      BasisSurf,
                                       occ::handle<StepGeom_Pcurve>&             thePCurve,
                                       const int                                 last)
{
  int NbAssGeom = SurfCurve->NbAssociatedGeometry();
  thePCurve.Nullify();
  for (int i = last + 1; i <= NbAssGeom; i++)
  {
    thePCurve = SurfCurve->AssociatedGeometryValue(i).Pcurve();
    if (!thePCurve.IsNull())
    {
      if (thePCurve->BasisSurface() == BasisSurf)
        return i;
    }
  }
  thePCurve.Nullify();
  return 0;
}

bool StepToTopoDS_GeometricTool::IsSeamCurve(const occ::handle<StepGeom_SurfaceCurve>& SurfCurve,
                                             const occ::handle<StepGeom_Surface>&      Surf,
                                             const occ::handle<StepShape_Edge>&        StepEdge,
                                             const occ::handle<StepShape_EdgeLoop>&    EdgeLoop)
{
  if (SurfCurve->IsKind(STANDARD_TYPE(StepGeom_SeamCurve)))
    return true;

  if (SurfCurve->NbAssociatedGeometry() != 2)
    return false;

  occ::handle<StepGeom_Pcurve> StepPCurve1 = SurfCurve->AssociatedGeometryValue(1).Pcurve();
  occ::handle<StepGeom_Pcurve> StepPCurve2 = SurfCurve->AssociatedGeometryValue(2).Pcurve();

  if ((!StepPCurve1.IsNull() && !StepPCurve2.IsNull()) && (StepPCurve1->BasisSurface() == Surf)
      && (StepPCurve2->BasisSurface() == Surf))
  {

    int NbEdge = EdgeLoop->NbEdgeList();
    int nbOE   = 0;

    occ::handle<StepShape_OrientedEdge> OrEdge;

    for (int i = 1; i <= NbEdge; i++)
    {
      OrEdge = EdgeLoop->EdgeListValue(i);
      if (StepEdge == OrEdge->EdgeElement())
        nbOE++;
    }

    if (nbOE == 2)
      return true;
  }
  return false;
}

bool StepToTopoDS_GeometricTool::IsLikeSeam(const occ::handle<StepGeom_SurfaceCurve>& SurfCurve,
                                            const occ::handle<StepGeom_Surface>&      Surf,
                                            const occ::handle<StepShape_Edge>&        StepEdge,
                                            const occ::handle<StepShape_EdgeLoop>&    EdgeLoop)
{
  if (SurfCurve->NbAssociatedGeometry() != 2)
    return false;

  occ::handle<StepGeom_Pcurve> StepPCurve1 = SurfCurve->AssociatedGeometryValue(1).Pcurve();
  occ::handle<StepGeom_Pcurve> StepPCurve2 = SurfCurve->AssociatedGeometryValue(2).Pcurve();

  if ((!StepPCurve1.IsNull() && !StepPCurve2.IsNull()) && (StepPCurve1->BasisSurface() == Surf)
      && (StepPCurve2->BasisSurface() == Surf))
  {

    int NbEdge = EdgeLoop->NbEdgeList();
    int nbOE   = 0;

    occ::handle<StepShape_OrientedEdge> OrEdge;

    for (int i = 1; i <= NbEdge; i++)
    {
      OrEdge = EdgeLoop->EdgeListValue(i);
      if (StepEdge == OrEdge->EdgeElement())
        nbOE++;
    }

    if (nbOE == 1)
    {

      occ::handle<StepGeom_Line> line1 =
        occ::down_cast<StepGeom_Line>(StepPCurve1->ReferenceToCurve()->ItemsValue(1));
      occ::handle<StepGeom_Line> line2 =
        occ::down_cast<StepGeom_Line>(StepPCurve2->ReferenceToCurve()->ItemsValue(1));
      if (!line1.IsNull() && !line2.IsNull())
      {

        double DeltaX =
          std::abs(line1->Pnt()->CoordinatesValue(1) - line2->Pnt()->CoordinatesValue(1));
        double DeltaY =
          std::abs(line1->Pnt()->CoordinatesValue(2) - line2->Pnt()->CoordinatesValue(2));

        double DeltaDirX = std::abs(line1->Dir()->Orientation()->DirectionRatiosValue(1)
                                    - line2->Dir()->Orientation()->DirectionRatiosValue(1));
        double DeltaDirY = std::abs(line1->Dir()->Orientation()->DirectionRatiosValue(2)
                                    - line2->Dir()->Orientation()->DirectionRatiosValue(2));

        double preci2d = Precision::PConfusion();

        if ((DeltaX < preci2d) || (DeltaY < preci2d))
          return ((DeltaDirX < preci2d) && (DeltaDirY < preci2d));
        else
          return false;
      }
      else
        return false;
    }
    return false;
  }
  return false;
}

bool StepToTopoDS_GeometricTool::UpdateParam3d(const occ::handle<Geom_Curve>& theCurve,
                                               double&                        w1,
                                               double&                        w2,
                                               const double                   preci)
{

  double cf = theCurve->FirstParameter();
  double cl = theCurve->LastParameter();

  if (theCurve->IsKind(STANDARD_TYPE(Geom_BoundedCurve)) && !theCurve->IsClosed())
  {
    if (w1 < cf)
    {
#ifdef OCCT_DEBUG
      std::cout << "Update Edge First Parameter to Curve First Parameter" << std::endl;
#endif
      w1 = cf;
    }
    else if (w1 > cl)
    {
#ifdef OCCT_DEBUG
      std::cout << "Update Edge First Parameter to Curve Last Parameter" << std::endl;
#endif
      w1 = cl;
    }
    if (w2 < cf)
    {
#ifdef OCCT_DEBUG
      std::cout << "Update Edge Last Parameter to Curve First Parameter" << std::endl;
#endif
      w2 = cf;
    }
    else if (w2 > cl)
    {
#ifdef OCCT_DEBUG
      std::cout << "Update Edge Last Parameter to Curve Last Parameter" << std::endl;
#endif
      w2 = cl;
    }
  }

  if (w1 < w2)
    return true;

  if (theCurve->IsPeriodic())
  {

    ElCLib::AdjustPeriodic(cf, cl, Precision::PConfusion(), w1, w2);
  }
  else if (theCurve->IsClosed())
  {

    if (std::abs(w2 - cf) < Precision::PConfusion())
    {
      w2 = cl;
    }

    else if (std::abs(w1 - cl) < Precision::PConfusion())
    {
      w1 = cf;
    }

    else
    {

      if (theCurve->Value(w1).Distance(theCurve->Value(cf)) < preci)
      {
        w1 = cf;
      }
      if (theCurve->Value(w2).Distance(theCurve->Value(cl)) < preci)
      {
        w2 = cl;
      }
      if (fabs(w2 - w1) < Precision::PConfusion())
      {
        w1 = cf;
        w2 = cl;
      }
      else if (w1 > w2)
      {
#ifdef OCCT_DEBUG
        std::cout << "Warning : parameter range of edge crossing non periodic curve origin"
                  << std::endl;
#endif
        double tmp = w1;
        w1         = w2;
        w2         = tmp;
      }
    }
  }

  else if (theCurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    occ::handle<Geom_BSplineCurve> aBSpline = occ::down_cast<Geom_BSplineCurve>(theCurve);
    if (aBSpline->StartPoint().Distance(aBSpline->EndPoint()) <= preci)
    {

      if (std::abs(w2 - cf) < Precision::PConfusion())
      {
        w2 = cl;
      }

      else if (std::abs(w1 - cl) < Precision::PConfusion())
      {
        w1 = cf;
      }

      else
      {
#ifdef OCCT_DEBUG
        std::cout << "Warning : parameter range of edge crossing non periodic curve origin"
                  << std::endl;
#endif
        double tmp = w1;
        w1         = w2;
        w2         = tmp;
      }
    }

    else if (w1 > w2)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: parameter range is bad; curve reversed" << std::endl;
#endif
      w1 = theCurve->ReversedParameter(w1);
      w2 = theCurve->ReversedParameter(w2);
      theCurve->Reverse();
    }

    if (w1 == w2)
    {
      w1 = cf;
      w2 = cl;
      return false;
    }
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "UpdateParam3d Failed" << std::endl;
    std::cout << "  - Curve Type : " << theCurve->DynamicType() << std::endl;
    std::cout << "  - Param 1    : " << w1 << std::endl;
    std::cout << "  - Param 2    : " << w2 << std::endl;
#endif

    if (w1 > w2)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: parameter range is bad; curve reversed" << std::endl;
#endif
      w1 = theCurve->ReversedParameter(w1);
      w2 = theCurve->ReversedParameter(w2);
      theCurve->Reverse();
    }

    if (w1 == w2)
    {
      w1 -= Precision::PConfusion();
      w2 += Precision::PConfusion();
    }
    return false;
  }
  return true;
}
