#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepTool_OutCurveType.hpp>
#include <Standard_Integer.hpp>

class TopOpeBRepTool_GeomTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_GeomTool(
    const TopOpeBRepTool_OutCurveType TypeC3D = TopOpeBRepTool_BSPLINE1,
    const bool                        CompC3D = true,
    const bool                        CompPC1 = true,
    const bool                        CompPC2 = true);

  Standard_EXPORT void Define(const TopOpeBRepTool_OutCurveType TypeC3D,
                              const bool                        CompC3D,
                              const bool                        CompPC1,
                              const bool                        CompPC2);

  Standard_EXPORT void Define(const TopOpeBRepTool_OutCurveType TypeC3D);

  Standard_EXPORT void DefineCurves(const bool CompC3D);

  Standard_EXPORT void DefinePCurves1(const bool CompPC1);

  Standard_EXPORT void DefinePCurves2(const bool CompPC2);

  Standard_EXPORT void Define(const TopOpeBRepTool_GeomTool& GT);

  Standard_EXPORT void GetTolerances(double& tol3d, double& tol2d) const;

  Standard_EXPORT void SetTolerances(const double tol3d, const double tol2d);

  Standard_EXPORT int NbPntMax() const;

  Standard_EXPORT void SetNbPntMax(const int NbPntMax);

  Standard_EXPORT TopOpeBRepTool_OutCurveType TypeC3D() const;

  Standard_EXPORT bool CompC3D() const;

  Standard_EXPORT bool CompPC1() const;

  Standard_EXPORT bool CompPC2() const;

protected:
  TopOpeBRepTool_OutCurveType myTypeC3D;
  bool                        myCompC3D;
  bool                        myCompPC1;
  bool                        myCompPC2;

private:
  double myTol3d;
  double myTol2d;
  int    myNbPntMax;
};
