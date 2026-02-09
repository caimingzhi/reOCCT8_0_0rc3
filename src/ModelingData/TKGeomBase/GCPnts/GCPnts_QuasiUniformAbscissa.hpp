#pragma once

#include <StdFail_NotDone.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class Adaptor3d_Curve;
class Adaptor2d_Curve2d;

class GCPnts_QuasiUniformAbscissa
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCPnts_QuasiUniformAbscissa();

  Standard_EXPORT GCPnts_QuasiUniformAbscissa(const Adaptor3d_Curve& theC, const int theNbPoints);

  Standard_EXPORT GCPnts_QuasiUniformAbscissa(const Adaptor3d_Curve& theC,
                                              const int              theNbPoints,
                                              const double           theU1,
                                              const double           theU2);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC, const int theNbPoints);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const int              theNbPoints,
                                  const double           theU1,
                                  const double           theU2);

  Standard_EXPORT GCPnts_QuasiUniformAbscissa(const Adaptor2d_Curve2d& theC, const int theNbPoints);

  Standard_EXPORT GCPnts_QuasiUniformAbscissa(const Adaptor2d_Curve2d& theC,
                                              const int                theNbPoints,
                                              const double             theU1,
                                              const double             theU2);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC, const int theNbPoints);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const int                theNbPoints,
                                  const double             theU1,
                                  const double             theU2);

  bool IsDone() const { return myDone; }

  int NbPoints() const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_QuasiUniformAbscissa::NbPoints()");
    return myNbPoints;
  }

  double Parameter(const int Index) const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_QuasiUniformAbscissa::Parameter()");
    return myParams->Value(Index);
  }

private:
  template <class TheCurve>
  void initialize(const TheCurve& theC,
                  const int       theNbPoints,
                  const double    theU1,
                  const double    theU2);

private:
  bool                                     myDone;
  int                                      myNbPoints;
  occ::handle<NCollection_HArray1<double>> myParams;
};
