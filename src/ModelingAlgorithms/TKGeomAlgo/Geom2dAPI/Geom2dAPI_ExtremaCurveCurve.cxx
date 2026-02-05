#include <Extrema_ExtCC2d.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <Geom2dAPI_ExtremaCurveCurve.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

//=================================================================================================

// Geom2dAPI_ExtremaCurveCurve::Geom2dAPI_ExtremaCurveCurve()
//{
//}
//=================================================================================================

Geom2dAPI_ExtremaCurveCurve::Geom2dAPI_ExtremaCurveCurve(const occ::handle<Geom2d_Curve>& C1,
                                                         const occ::handle<Geom2d_Curve>& C2,
                                                         const double                     U1min,
                                                         const double                     U1max,
                                                         const double                     U2min,
                                                         const double                     U2max)
{
  myC1.Load(C1, U1min, U1max);
  myC2.Load(C2, U2min, U2max);
  Extrema_ExtCC2d theExtCC(myC1, myC2);

  myExtCC = theExtCC;

  myIsDone = myExtCC.IsDone() && (myExtCC.NbExt() > 0);

  if (myIsDone)
  {
    // evaluate the lower distance and its index;

    double Dist2, Dist2Min = myExtCC.SquareDistance(1);
    myIndex = 1;

    for (int i = 2; i <= myExtCC.NbExt(); i++)
    {
      Dist2 = myExtCC.SquareDistance(i);
      if (Dist2 < Dist2Min)
      {
        Dist2Min = Dist2;
        myIndex  = i;
      }
    }
  }
}

//=================================================================================================

int Geom2dAPI_ExtremaCurveCurve::NbExtrema() const
{
  if (myIsDone)
    return myExtCC.NbExt();
  else
    return 0;
}

//=================================================================================================

void Geom2dAPI_ExtremaCurveCurve::Points(const int Index, gp_Pnt2d& P1, gp_Pnt2d& P2) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbExtrema(),
                               "Geom2dAPI_ExtremaCurveCurve::Points");

  Extrema_POnCurv2d PC1, PC2;
  myExtCC.Points(Index, PC1, PC2);

  P1 = PC1.Value();
  P2 = PC2.Value();
}

//=================================================================================================

void Geom2dAPI_ExtremaCurveCurve::Parameters(const int Index, double& U1, double& U2) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbExtrema(),
                               "Geom2dAPI_ExtremaCurveCurve::Parameters");

  Extrema_POnCurv2d PC1, PC2;
  myExtCC.Points(Index, PC1, PC2);

  U1 = PC1.Parameter();
  U2 = PC2.Parameter();
}

//=================================================================================================

double Geom2dAPI_ExtremaCurveCurve::Distance(const int Index) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbExtrema(),
                               "Geom2dAPI_ExtremaCurveCurve:Distance");

  return sqrt(myExtCC.SquareDistance(Index));
}

//=================================================================================================

void Geom2dAPI_ExtremaCurveCurve::NearestPoints(gp_Pnt2d& P1, gp_Pnt2d& P2) const
{
  StdFail_NotDone_Raise_if(!myIsDone, "Geom2dAPI_ExtremaCurveCurve:NearestPoints");

  Points(myIndex, P1, P2);
}

//=================================================================================================

void Geom2dAPI_ExtremaCurveCurve::LowerDistanceParameters(double& U1, double& U2) const
{
  StdFail_NotDone_Raise_if(!myIsDone, "Geom2dAPI_ExtremaCurveCurve:LowerDistanceParameters");

  Parameters(myIndex, U1, U2);
}

//=================================================================================================

double Geom2dAPI_ExtremaCurveCurve::LowerDistance() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "Geom2dAPI_ExtremaCurveCurve:LowerDistance");

  return sqrt(myExtCC.SquareDistance(myIndex));
}

//=================================================================================================

Geom2dAPI_ExtremaCurveCurve::operator double() const
{
  return LowerDistance();
}

//=================================================================================================

Geom2dAPI_ExtremaCurveCurve::operator int() const
{
  return myExtCC.NbExt();
}
