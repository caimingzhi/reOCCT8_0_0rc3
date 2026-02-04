#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt2d.hpp>

//! Bspline approximation of a surface.
class AppBlend_Approx
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual bool IsDone() const = 0;

  Standard_EXPORT virtual void SurfShape(int& UDegree,
                                         int& VDegree,
                                         int& NbUPoles,
                                         int& NbVPoles,
                                         int& NbUKnots,
                                         int& NbVKnots) const = 0;

  Standard_EXPORT virtual void Surface(NCollection_Array2<gp_Pnt>& TPoles,
                                       NCollection_Array2<double>& TWeights,
                                       NCollection_Array1<double>& TUKnots,
                                       NCollection_Array1<double>& TVKnots,
                                       NCollection_Array1<int>&    TUMults,
                                       NCollection_Array1<int>&    TVMults) const = 0;

  Standard_EXPORT virtual int UDegree() const = 0;

  Standard_EXPORT virtual int VDegree() const = 0;

  Standard_EXPORT virtual const NCollection_Array2<gp_Pnt>& SurfPoles() const = 0;

  Standard_EXPORT virtual const NCollection_Array2<double>& SurfWeights() const = 0;

  Standard_EXPORT virtual const NCollection_Array1<double>& SurfUKnots() const = 0;

  Standard_EXPORT virtual const NCollection_Array1<double>& SurfVKnots() const = 0;

  Standard_EXPORT virtual const NCollection_Array1<int>& SurfUMults() const = 0;

  Standard_EXPORT virtual const NCollection_Array1<int>& SurfVMults() const = 0;

  Standard_EXPORT virtual int NbCurves2d() const = 0;

  Standard_EXPORT virtual void Curves2dShape(int& Degree, int& NbPoles, int& NbKnots) const = 0;

  Standard_EXPORT virtual void Curve2d(const int                     Index,
                                       NCollection_Array1<gp_Pnt2d>& TPoles,
                                       NCollection_Array1<double>&   TKnots,
                                       NCollection_Array1<int>&      TMults) const = 0;

  Standard_EXPORT virtual int Curves2dDegree() const = 0;

  Standard_EXPORT virtual const NCollection_Array1<gp_Pnt2d>& Curve2dPoles(
    const int Index) const = 0;

  Standard_EXPORT virtual const NCollection_Array1<double>& Curves2dKnots() const = 0;

  Standard_EXPORT virtual const NCollection_Array1<int>& Curves2dMults() const = 0;

  Standard_EXPORT virtual void TolReached(double& Tol3d, double& Tol2d) const = 0;

  Standard_EXPORT virtual double TolCurveOnSurf(const int Index) const = 0;
  Standard_EXPORT virtual ~AppBlend_Approx();
};

