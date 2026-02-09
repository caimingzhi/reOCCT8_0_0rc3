#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>

class Convert_CompBezierCurvesToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Convert_CompBezierCurvesToBSplineCurve(const double AngularTolerance = 1.0e-4);

  Standard_EXPORT void AddCurve(const NCollection_Array1<gp_Pnt>& Poles);

  Standard_EXPORT void Perform();

  Standard_EXPORT int Degree() const;

  Standard_EXPORT int NbPoles() const;

  Standard_EXPORT void Poles(NCollection_Array1<gp_Pnt>& Poles) const;

  Standard_EXPORT int NbKnots() const;

  Standard_EXPORT void KnotsAndMults(NCollection_Array1<double>& Knots,
                                     NCollection_Array1<int>&    Mults) const;

private:
  NCollection_Sequence<occ::handle<NCollection_HArray1<gp_Pnt>>> mySequence;
  NCollection_Sequence<gp_Pnt>                                   CurvePoles;
  NCollection_Sequence<double>                                   CurveKnots;
  NCollection_Sequence<int>                                      KnotsMultiplicities;
  int                                                            myDegree;
  double                                                         myAngular;
  bool                                                           myDone;
};
