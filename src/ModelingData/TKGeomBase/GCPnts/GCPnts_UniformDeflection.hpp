#pragma once

#include <StdFail_NotDone.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>

class Adaptor3d_Curve;
class Adaptor2d_Curve2d;
class gp_Pnt;

class GCPnts_UniformDeflection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCPnts_UniformDeflection();

  Standard_EXPORT GCPnts_UniformDeflection(const Adaptor3d_Curve& theC,
                                           const double           theDeflection,
                                           const bool             theWithControl = true);

  Standard_EXPORT GCPnts_UniformDeflection(const Adaptor2d_Curve2d& theC,
                                           const double             theDeflection,
                                           const bool               theWithControl = true);

  Standard_EXPORT GCPnts_UniformDeflection(const Adaptor3d_Curve& theC,
                                           const double           theDeflection,
                                           const double           theU1,
                                           const double           theU2,
                                           const bool             theWithControl = true);

  Standard_EXPORT GCPnts_UniformDeflection(const Adaptor2d_Curve2d& theC,
                                           const double             theDeflection,
                                           const double             theU1,
                                           const double             theU2,
                                           const bool               theWithControl = true);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const double           theDeflection,
                                  const bool             theWithControl = true);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const double             theDeflection,
                                  const bool               theWithControl = true);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const double           theDeflection,
                                  const double           theU1,
                                  const double           theU2,
                                  const bool             theWithControl = true);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const double             theDeflection,
                                  const double             theU1,
                                  const double             theU2,
                                  const bool               theWithControl = true);

  bool IsDone() const { return myDone; }

  int NbPoints() const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_UniformDeflection::NbPoints()");
    return myParams.Length();
  }

  double Parameter(const int Index) const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_UniformDeflection::Parameter()");
    return myParams(Index);
  }

  Standard_EXPORT gp_Pnt Value(const int Index) const;

  double Deflection() const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_UniformDeflection::Deflection()");
    return myDeflection;
  }

private:
  template <class TheCurve>
  void initialize(const TheCurve& theC,
                  const double    theDeflection,
                  const double    theU1,
                  const double    theU2,
                  const bool      theWithControl);

private:
  bool                         myDone;
  double                       myDeflection;
  NCollection_Sequence<double> myParams;
  NCollection_Sequence<gp_Pnt> myPoints;
};
