#include <StdFail_NotDone.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

inline bool AppBlend_AppSurf::IsDone() const
{
  return done;
}

inline int AppBlend_AppSurf::UDegree() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return udeg;
}

inline int AppBlend_AppSurf::VDegree() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return vdeg;
}

inline const NCollection_Array2<gp_Pnt>& AppBlend_AppSurf::SurfPoles() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return tabPoles->Array2();
}

inline const NCollection_Array2<double>& AppBlend_AppSurf::SurfWeights() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return tabWeights->Array2();
}

inline const NCollection_Array1<double>& AppBlend_AppSurf::SurfUKnots() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return tabUKnots->Array1();
}

inline const NCollection_Array1<double>& AppBlend_AppSurf::SurfVKnots() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return tabVKnots->Array1();
}

inline const NCollection_Array1<int>& AppBlend_AppSurf::SurfUMults() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return tabUMults->Array1();
}

inline const NCollection_Array1<int>& AppBlend_AppSurf::SurfVMults() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return tabVMults->Array1();
}

inline int AppBlend_AppSurf::NbCurves2d() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return seqPoles2d.Length();
}

inline int AppBlend_AppSurf::Curves2dDegree() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (seqPoles2d.Length() == 0)
  {
    throw Standard_DomainError();
  }
  return vdeg;
}

inline const NCollection_Array1<gp_Pnt2d>& AppBlend_AppSurf::Curve2dPoles(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (seqPoles2d.Length() == 0)
  {
    throw Standard_DomainError();
  }
  return seqPoles2d(Index)->Array1();
}

inline const NCollection_Array1<double>& AppBlend_AppSurf::Curves2dKnots() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (seqPoles2d.Length() == 0)
  {
    throw Standard_DomainError();
  }
  return tabVKnots->Array1();
}

inline const NCollection_Array1<int>& AppBlend_AppSurf::Curves2dMults() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (seqPoles2d.Length() == 0)
  {
    throw Standard_DomainError();
  }
  return tabVMults->Array1();
}

inline void AppBlend_AppSurf::TolReached(double& Tol3d, double& Tol2d) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  Tol3d = tol3dreached;
  Tol2d = tol2dreached;
}
