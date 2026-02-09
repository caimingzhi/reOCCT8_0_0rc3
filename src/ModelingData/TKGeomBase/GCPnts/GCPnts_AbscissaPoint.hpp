#pragma once

#include <CPnts_AbscissaPoint.hpp>

class Adaptor3d_Curve;
class Adaptor2d_Curve2d;

class GCPnts_AbscissaPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double Length(const Adaptor3d_Curve& theC);

  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& theC);

  Standard_EXPORT static double Length(const Adaptor3d_Curve& theC, const double theTol);

  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& theC, const double theTol);

  Standard_EXPORT static double Length(const Adaptor3d_Curve& theC,
                                       const double           theU1,
                                       const double           theU2);

  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& theC,
                                       const double             theU1,
                                       const double             theU2);

  Standard_EXPORT static double Length(const Adaptor3d_Curve& theC,
                                       const double           theU1,
                                       const double           theU2,
                                       const double           theTol);

  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& theC,
                                       const double             theU1,
                                       const double             theU2,
                                       const double             theTol);

public:
  Standard_EXPORT GCPnts_AbscissaPoint();

  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor3d_Curve& theC,
                                       const double           theAbscissa,
                                       const double           theU0);

  Standard_EXPORT GCPnts_AbscissaPoint(const double           theTol,
                                       const Adaptor3d_Curve& theC,
                                       const double           theAbscissa,
                                       const double           theU0);

  Standard_EXPORT GCPnts_AbscissaPoint(const double             theTol,
                                       const Adaptor2d_Curve2d& theC,
                                       const double             theAbscissa,
                                       const double             theU0);

  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor2d_Curve2d& theC,
                                       const double             theAbscissa,
                                       const double             theU0);

  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor3d_Curve& theC,
                                       const double           theAbscissa,
                                       const double           theU0,
                                       const double           theUi);

  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor2d_Curve2d& theC,
                                       const double             theAbscissa,
                                       const double             theU0,
                                       const double             theUi);

  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor3d_Curve& theC,
                                       const double           theAbscissa,
                                       const double           theU0,
                                       const double           theUi,
                                       const double           theTol);

  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor2d_Curve2d& theC,
                                       const double             theAbscissa,
                                       const double             theU0,
                                       const double             theUi,
                                       const double             theTol);

  bool IsDone() const { return myComputer.IsDone(); }

  double Parameter() const { return myComputer.Parameter(); }

private:
  template <class TheCurve>
  static double length(const TheCurve& theC,
                       const double    theU1,
                       const double    theU2,
                       const double*   theTol);

  template <class TheCurve>
  void compute(const TheCurve& theC, const double theAbscissa, const double theU0);

  template <class TheCurve>
  void advCompute(const double    theTol,
                  const TheCurve& theC,
                  const double    theAbscissa,
                  const double    theU0);

private:
  CPnts_AbscissaPoint myComputer;
};
