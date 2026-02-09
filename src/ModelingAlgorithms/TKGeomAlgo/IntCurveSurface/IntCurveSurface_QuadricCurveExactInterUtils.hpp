#pragma once

#include <GeomAbs_SurfaceType.hpp>
#include <IntSurf_Quadric.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Sequence.hpp>
#include <math_FunctionAllRoots.hpp>
#include <math_FunctionSample.hpp>

namespace IntCurveSurface_QuadricCurveExactInterUtils
{

  constexpr double EPSX    = 0.00000000000001;
  constexpr double EPSDIST = 0.00000001;
  constexpr double EPSNUL  = 0.00000001;

  template <typename SurfaceType,
            typename SurfaceTool,
            typename CurveType,
            typename CurveTool,
            typename QuadCurvFuncType>
  void PerformIntersection(const SurfaceType&            theSurface,
                           const CurveType&              theCurve,
                           NCollection_Sequence<double>& thePnts,
                           NCollection_Sequence<double>& theIntv,
                           int&                          theNbPnts,
                           int&                          theNbIntv)
  {
    theNbPnts = -1;
    theNbIntv = -1;

    GeomAbs_SurfaceType aQuadricType = SurfaceTool::GetType(theSurface);
    IntSurf_Quadric     aQuadric;

    switch (aQuadricType)
    {
      case GeomAbs_Plane:
      {
        aQuadric.SetValue(SurfaceTool::Plane(theSurface));
        break;
      }
      case GeomAbs_Cylinder:
      {
        aQuadric.SetValue(SurfaceTool::Cylinder(theSurface));
        break;
      }
      case GeomAbs_Cone:
      {
        aQuadric.SetValue(SurfaceTool::Cone(theSurface));
        break;
      }
      case GeomAbs_Sphere:
      {
        aQuadric.SetValue(SurfaceTool::Sphere(theSurface));
        break;
      }
      default:
      {
        break;
      }
    }

    int                        aNbIntervals = CurveTool::NbIntervals(theCurve, GeomAbs_C1);
    NCollection_Array1<double> anIntervals(1, aNbIntervals + 1);
    int                        ii;

    CurveTool::Intervals(theCurve, anIntervals, GeomAbs_C1);

    for (ii = 1; ii <= aNbIntervals; ii++)
    {
      double U1 = anIntervals.Value(ii);
      double U2 = anIntervals.Value(ii + 1);

      math_FunctionSample   aSample(U1, U2, CurveTool::NbSamples(theCurve, U1, U2));
      QuadCurvFuncType      aFunction(aQuadric, theCurve);
      math_FunctionAllRoots aRoots(aFunction, aSample, EPSX, EPSDIST, EPSNUL);

      if (aRoots.IsDone())
      {
        int aNbPoints   = aRoots.NbPoints();
        int aNbRootIntv = aRoots.NbIntervals();

        for (int i = 1; i <= aNbPoints; i++)
        {
          thePnts.Append(aRoots.GetPoint(i));
        }

        double a, b;
        for (int i = 1; i <= aNbRootIntv; i++)
        {
          aRoots.GetInterval(i, a, b);
          theIntv.Append(a);
          theIntv.Append(b);
        }
      }
      else
      {
        break;
      }
    }

    if (ii > aNbIntervals)
    {
      theNbPnts = thePnts.Length();
      theNbIntv = theIntv.Length() / 2;
    }
  }

} // namespace IntCurveSurface_QuadricCurveExactInterUtils
