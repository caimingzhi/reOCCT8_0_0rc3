#pragma once

#include <StdFail_NotDone.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
#include <GeomAbs_Shape.hpp>

class Adaptor3d_Curve;
class Adaptor2d_Curve2d;
class gp_Pnt;

class GCPnts_QuasiUniformDeflection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCPnts_QuasiUniformDeflection();

  Standard_EXPORT GCPnts_QuasiUniformDeflection(const Adaptor3d_Curve& theC,
                                                const double           theDeflection,
                                                const GeomAbs_Shape    theContinuity = GeomAbs_C1);

  Standard_EXPORT GCPnts_QuasiUniformDeflection(const Adaptor2d_Curve2d& theC,
                                                const double             theDeflection,
                                                const GeomAbs_Shape theContinuity = GeomAbs_C1);

  Standard_EXPORT GCPnts_QuasiUniformDeflection(const Adaptor3d_Curve& theC,
                                                const double           theDeflection,
                                                const double           theU1,
                                                const double           theU2,
                                                const GeomAbs_Shape    theContinuity = GeomAbs_C1);

  Standard_EXPORT GCPnts_QuasiUniformDeflection(const Adaptor2d_Curve2d& theC,
                                                const double             theDeflection,
                                                const double             theU1,
                                                const double             theU2,
                                                const GeomAbs_Shape theContinuity = GeomAbs_C1);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const double           theDeflection,
                                  const GeomAbs_Shape    theContinuity = GeomAbs_C1);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const double             theDeflection,
                                  const GeomAbs_Shape      theContinuity = GeomAbs_C1);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const double           theDeflection,
                                  const double           theU1,
                                  const double           theU2,
                                  const GeomAbs_Shape    theContinuity = GeomAbs_C1);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const double             theDeflection,
                                  const double             theU1,
                                  const double             theU2,
                                  const GeomAbs_Shape      theContinuity = GeomAbs_C1);

  bool IsDone() const { return myDone; }

  int NbPoints() const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_QuasiUniformDeflection::NbPoints()");
    return myParams.Length();
  }

  double Parameter(const int Index) const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_QuasiUniformDeflection::Parameter()");
    return myParams(Index);
  }

  Standard_EXPORT gp_Pnt Value(const int Index) const;

  double Deflection() const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_QuasiUniformDeflection::Deflection()");
    return myDeflection;
  }

private:
  template <class TheCurve>
  void initialize(const TheCurve&     theC,
                  const double        theDeflection,
                  const double        theU1,
                  const double        theU2,
                  const GeomAbs_Shape theContinuity);

private:
  bool                         myDone;
  double                       myDeflection;
  NCollection_Sequence<double> myParams;
  NCollection_Sequence<gp_Pnt> myPoints;
  GeomAbs_Shape                myCont;
};
