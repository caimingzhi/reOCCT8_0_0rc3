#pragma once

#include <StdFail_NotDone.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class Adaptor3d_Curve;
class Adaptor2d_Curve2d;

class GCPnts_UniformAbscissa
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCPnts_UniformAbscissa();

  Standard_EXPORT GCPnts_UniformAbscissa(const Adaptor3d_Curve& theC,
                                         const double           theAbscissa,
                                         const double           theToler = -1);

  Standard_EXPORT GCPnts_UniformAbscissa(const Adaptor3d_Curve& theC,
                                         const double           theAbscissa,
                                         const double           theU1,
                                         const double           theU2,
                                         const double           theToler = -1);

  Standard_EXPORT GCPnts_UniformAbscissa(const Adaptor3d_Curve& theC,
                                         const int              theNbPoints,
                                         const double           theToler = -1);

  Standard_EXPORT GCPnts_UniformAbscissa(const Adaptor3d_Curve& theC,
                                         const int              theNbPoints,
                                         const double           theU1,
                                         const double           theU2,
                                         const double           theToler = -1);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const double           theAbscissa,
                                  const double           theToler = -1);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const double           theAbscissa,
                                  const double           theU1,
                                  const double           theU2,
                                  const double           theToler = -1);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const int              theNbPoints,
                                  const double           theToler = -1);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const int              theNbPoints,
                                  const double           theU1,
                                  const double           theU2,
                                  const double           theToler = -1);

public:
  Standard_EXPORT GCPnts_UniformAbscissa(const Adaptor2d_Curve2d& theC,
                                         const double             theAbscissa,
                                         const double             theToler = -1);

  Standard_EXPORT GCPnts_UniformAbscissa(const Adaptor2d_Curve2d& theC,
                                         const double             theAbscissa,
                                         const double             theU1,
                                         const double             theU2,
                                         const double             theToler = -1);

  Standard_EXPORT GCPnts_UniformAbscissa(const Adaptor2d_Curve2d& theC,
                                         const int                theNbPoints,
                                         const double             theToler = -1);

  Standard_EXPORT GCPnts_UniformAbscissa(const Adaptor2d_Curve2d& theC,
                                         const int                theNbPoints,
                                         const double             theU1,
                                         const double             theU2,
                                         const double             theToler = -1);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const double             theAbscissa,
                                  const double             theToler = -1);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const double             theAbscissa,
                                  const double             theU1,
                                  const double             theU2,
                                  const double             theToler = -1);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const int                theNbPoints,
                                  const double             theToler = -1);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const int                theNbPoints,
                                  const double             theU1,
                                  const double             theU2,
                                  const double             theToler = -1);

  bool IsDone() const { return myDone; }

  int NbPoints() const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_UniformAbscissa::NbPoints()");
    return myNbPoints;
  }

  double Parameter(const int Index) const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_UniformAbscissa::Parameter()");
    return myParams->Value(Index);
  }

  double Abscissa() const
  {
    StdFail_NotDone_Raise_if(!myDone, "GCPnts_UniformAbscissa::Abscissa()");
    return myAbscissa;
  }

private:
  template <class TheCurve>
  void initialize(const TheCurve& theC,
                  const double    theAbscissa,
                  const double    theU1,
                  const double    theU2,
                  const double    theTol);

  template <class TheCurve>
  void initialize(const TheCurve& theC,
                  const int       theNbPoints,
                  const double    theU1,
                  const double    theU2,
                  const double    theTol);

private:
  bool                                     myDone;
  int                                      myNbPoints;
  double                                   myAbscissa;
  occ::handle<NCollection_HArray1<double>> myParams;
};
