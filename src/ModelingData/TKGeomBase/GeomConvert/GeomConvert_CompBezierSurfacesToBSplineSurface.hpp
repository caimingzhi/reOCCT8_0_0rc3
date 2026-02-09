#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Geom_BezierSurface.hpp>
#include <GeomAbs_Shape.hpp>

class GeomConvert_CompBezierSurfacesToBSplineSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_CompBezierSurfacesToBSplineSurface(
    const NCollection_Array2<occ::handle<Geom_BezierSurface>>& Beziers);

  Standard_EXPORT GeomConvert_CompBezierSurfacesToBSplineSurface(
    const NCollection_Array2<occ::handle<Geom_BezierSurface>>& Beziers,
    const double                                               Tolerance,
    const bool                                                 RemoveKnots = true);

  Standard_EXPORT GeomConvert_CompBezierSurfacesToBSplineSurface(
    const NCollection_Array2<occ::handle<Geom_BezierSurface>>& Beziers,
    const NCollection_Array1<double>&                          UKnots,
    const NCollection_Array1<double>&                          VKnots,
    const GeomAbs_Shape                                        UContinuity = GeomAbs_C0,
    const GeomAbs_Shape                                        VContinuity = GeomAbs_C0,
    const double                                               Tolerance   = 1.0e-4);

  int NbUKnots() const;

  int NbUPoles() const;

  int NbVKnots() const;

  int NbVPoles() const;

  const occ::handle<NCollection_HArray2<gp_Pnt>>& Poles() const;

  const occ::handle<NCollection_HArray1<double>>& UKnots() const;

  int UDegree() const;

  const occ::handle<NCollection_HArray1<double>>& VKnots() const;

  int VDegree() const;

  const occ::handle<NCollection_HArray1<int>>& UMultiplicities() const;

  const occ::handle<NCollection_HArray1<int>>& VMultiplicities() const;

  Standard_EXPORT bool IsDone() const;

private:
  Standard_EXPORT void Perform(const NCollection_Array2<occ::handle<Geom_BezierSurface>>& Beziers);

  int                                      myUDegree;
  int                                      myVDegree;
  occ::handle<NCollection_HArray1<int>>    myVMults;
  occ::handle<NCollection_HArray1<int>>    myUMults;
  occ::handle<NCollection_HArray1<double>> myUKnots;
  occ::handle<NCollection_HArray1<double>> myVKnots;
  occ::handle<NCollection_HArray2<gp_Pnt>> myPoles;
  bool                                     isrational;
  bool                                     myDone;
};

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

inline int GeomConvert_CompBezierSurfacesToBSplineSurface::NbUKnots() const

{
  return myUKnots->Length();
}

inline int GeomConvert_CompBezierSurfacesToBSplineSurface::NbUPoles() const

{
  return myPoles->ColLength();
}

inline int GeomConvert_CompBezierSurfacesToBSplineSurface::NbVKnots() const

{
  return myVKnots->Length();
}

inline int GeomConvert_CompBezierSurfacesToBSplineSurface::NbVPoles() const

{
  return myPoles->RowLength();
}

inline const occ::handle<NCollection_HArray2<gp_Pnt>>&
  GeomConvert_CompBezierSurfacesToBSplineSurface::Poles() const

{
  return myPoles;
}

inline const occ::handle<NCollection_HArray1<double>>&
  GeomConvert_CompBezierSurfacesToBSplineSurface::UKnots() const

{
  return myUKnots;
}

inline int GeomConvert_CompBezierSurfacesToBSplineSurface::UDegree() const

{
  return myUDegree;
}

inline const occ::handle<NCollection_HArray1<double>>&
  GeomConvert_CompBezierSurfacesToBSplineSurface::VKnots() const

{
  return myVKnots;
}

inline int GeomConvert_CompBezierSurfacesToBSplineSurface::VDegree() const

{
  return myVDegree;
}

inline const occ::handle<NCollection_HArray1<int>>& GeomConvert_CompBezierSurfacesToBSplineSurface::
  UMultiplicities() const

{
  return myUMults;
}

inline const occ::handle<NCollection_HArray1<int>>& GeomConvert_CompBezierSurfacesToBSplineSurface::
  VMultiplicities() const

{
  return myVMults;
}
